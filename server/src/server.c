#include "../include/pool.h"
#include "../include/tcp.h"
#include "../include/epoll.h"

int exit_pipe[2];
void sigFunc(int signum){
#ifdef _DEBUG
    printf("signal is coming\n");
#endif
    write(exit_pipe[1], &signum, 4);
}

// 输入参数ip，port，thread_num，capacity of taskque
int main(int argc, char **argv){
    
    ARGS_CHECK(argc, 5);
    pipe(exit_pipe);

    if(fork()){
        close(exit_pipe[0]);
        signal(SIGUSR1, sigFunc);
        wait(NULL);
        exit(0);
    }
    
    close(exit_pipe[1]);
    int thread_num = atoi(argv[3]);
    int que_capacity = atoi(argv[4]);
    int ret;
    // 线程池结构体
    ThreadPool thread_pool;
    bzero(&thread_pool, sizeof(ThreadPool));

    // 初始化线程池结构体
    threadPoolInit(&thread_pool, thread_num, que_capacity);
    // 启动线程池
    threadPoolStart(&thread_pool);
   
    // 创建TCP监听套接字
    int socket_fd;
    tcpInit(&socket_fd, argv[1], argv[2]);
    
    int epfd;
    epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    epollAddFd(epfd, socket_fd);
    epollAddFd(epfd, exit_pipe[0]);
    int ready_num = 0;
    struct epoll_event evs[10];
    bzero(evs, sizeof(evs));

    int client_fd;
    while(1){
        ready_num = epoll_wait(epfd, evs, 10, -1);
        for(int i = 0; i < ready_num; ++i){
            if(evs[i].data.fd == socket_fd){
                client_fd = accept(socket_fd, NULL, NULL);
                ERROR_CHECK(client_fd, -1, "accept");
                pQueNode p_node = (pQueNode)calloc(1, sizeof(QueNode));
                p_node->client_fd = client_fd;
                // 加入任务队列中
                pthread_mutex_lock(&(thread_pool.task_que.mutex));
                ret = taskQueInsert(&(thread_pool.task_que), p_node);
                pthread_mutex_unlock(&(thread_pool.task_que.mutex));
                // 唤醒子线程
                pthread_cond_signal(&(thread_pool.task_que.cond));
            }// endif
            // 通知子线程退出
            else if(evs[i].data.fd == exit_pipe[0]){
#ifdef _DEBUG
                printf("pipe can read\n");
#endif
                thread_pool.task_que.exit_flag = 1;
                // 给所有线程发消息
                pthread_cond_broadcast(&thread_pool.task_que.cond);

                for(int j = 0; j < thread_pool.thread_num; ++j){
                    pthread_join(thread_pool.pthid[j], NULL);
                }
                
#ifdef _DEBUG
                printf("main thread exit\n");
#endif
                exit(0);
            }
        }// endfor

    }// endwhile

}
