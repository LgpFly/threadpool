#include "../include/head.h"
#include "../include/transfile.h"
int main(int argc, char **argv){
    ARGS_CHECK(argc, 3);
    
    int ret;
    int socket_fd;
    char buf[10];
    bzero(buf, sizeof(buf));
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");

    struct sockaddr_in cli_addr;
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[2]));
    cli_addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    ret = connect(socket_fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
    ERROR_CHECK(ret, -1, "connect");
    
    ret = recvFile(socket_fd);
    if(-1 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
    }
    if(0 == ret){
        printf("download file success\n");
    }
    
}
