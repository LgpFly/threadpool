# cmake book

1. 编译单个可执行文件
   ```cmake
    cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
    project(recipe-01 LANGUAGES CXX)
    add_executable(hello-world hello-world.cpp)
    ```
    1. 第一行是得写明版本号
    2. 项目名得写上 添加可执行文件和他所依赖的文件
2. 编译
    1. cmake -H -Bbuild 等同于 mkdir -p build, cd build, cmake ..
    2. cmake --build . 相当于 make
    3. cmake --build . --target <target-name>
       1. 默认是all 也就是所有都构建出来
       2. clean 删除
3. if-elseif-else-endif 的用法
   1. 比较是否定义、数值、字符串、检查文件是否存在、检查操作系统类型和编译器 
   ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(MyProject)

    # 设置变量
    set(VERSION 2)
    option(ENABLE_FEATURE "Enable feature" ON)

    # 检查变量值
    if(VERSION EQUAL 1)
        message("Version is 1")
    elseif(VERSION GREATER 1)
        message("Version is greater than 1")
    else()
        message("Version is less than 1")
    endif()

    # 检查文件是否存在
    if(EXISTS "${CMAKE_SOURCE_DIR}/config.txt")
        message("config.txt exists")
    else()
        message("config.txt does not exist")
    endif()

    # 检查操作系统类型
    if(WIN32)
        message("This is a Windows system")
    elseif(UNIX)
        message("This is a Unix-like system")
    endif()

    # 结合 option 和 if
    if(ENABLE_FEATURE)
        message("Feature is enabled")
    else()
        message("Feature is disabled")
    endif()

    # 添加可执行文件
    add_executable(MyExecutable main.cpp)

   ```
4. 列表的运用
   ```cmake
   cmake_minimum_required(VERSION 3.10)
    project(ListExample)

    # 创建和初始化列表
    set(MY_LIST "item1" "item2" "item3")

    # 获取列表长度
    list(LENGTH MY_LIST length)
    message("Length of MY_LIST: ${length}")

    # 获取列表元素
    list(GET MY_LIST 1 second_item)
    message("Second item in MY_LIST: ${second_item}")

    # 查找列表元素
    list(FIND MY_LIST "item2" index)
    if(index EQUAL -1)
        message("item2 not found in MY_LIST")
    else()
        message("item2 found at index: ${index}")
    endif()

    # 追加元素到列表
    list(APPEND MY_LIST "item4" "item5")
    message("MY_LIST after append: ${MY_LIST}")

    # 插入元素到列表
    list(INSERT MY_LIST 1 "new_item")
    message("MY_LIST after insert: ${MY_LIST}")

    # 移除列表中的元素
    list(REMOVE_ITEM MY_LIST "item2")
    message("MY_LIST after remove item: ${MY_LIST}")

    # 移除列表中的位置元素
    list(REMOVE_AT MY_LIST 0)
    message("MY_LIST after remove at: ${MY_LIST}")

    # 移除列表中的重复元素
    list(REMOVE_DUPLICATES MY_LIST)
    message("MY_LIST after remove duplicates: ${MY_LIST}")

    # 子列表（切片）
    list(SUBLIST MY_LIST 1 2 sublist)
    message("Sublist: ${sublist}")

    # 列表反转
    list(REVERSE MY_LIST)
    message("Reversed MY_LIST: ${MY_LIST}")

   ```
5. foreach的用法
   1. foreach(loop_var arg1 arg2 ...) : 其中提供循环变量和显式项列表。当为sources_with_lower_optimization中的项打印编译器标志集时，使用此表单。注意，如果项目列表位于变量中，则必须显式展开它；也就是说，${sources_with_lower_optimization}必须作为参数传递。
   2. 通过指定一个范围，可以对整数进行循环，例如：foreach(loop_var range total)或foreach(loop_var range start stop [step])。
   3. 对列表值变量的循环，例如：foreach(loop_var IN LISTS [list1[...]]) 。参数解释为列表，其内容就会自动展开。
   4. 对变量的循环，例如： foreach(loop_var IN ITEMS [item1 [...]])。参数的内容没有展开。
6. 为文件设置属性
   1. 设置 set_source_files_properties(${_source} PROPERTIES COMPILE_FLAGS -O2)
   2. 获得 get_source_file_property(_flags ${_source} COMPILE_FLAGS)
7. 添加库 add_library(message STATIC/SHARED Message.hpp Message.cpp)
8. 连接库 add_executable(hello-world hello-world.cpp),  target_link_libraries(hello-world message)
9. 显示选项 cmake -D可以设置选项，在外面为变量赋值
   1.  option(USE_LIBRARY "Compile sources into a library" OFF),设定初值
   2.  别的选项可以依赖这个值
    ```cmake

    include(CMakeDependentOption)

    # second option depends on the value of the first
    cmake_dependent_option(
	    MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
	    "USE_LIBRARY" ON
	)
	
    # third option depends on the value of the first
    cmake_dependent_option(
	    MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
	    "USE_LIBRARY" ON
	)
    ```
10. 切换构建类型
    1. cmake -DCMAKE_BUILD_TYPE=Release/Debug
11. 设置编译选项
    
    target_compile_option(target PRIVATE "-fPIC")


    ```cmake
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions")
        list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
        list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
        list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
        list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wdocumentation")
        list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
    endif()

    ```
12. CMAKE_SYSTEM_NAME 指导是哪种操作系统
    ```cmake
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	    message(STATUS "Configuring on/for Linux")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	    message(STATUS "Configuring on/for macOS")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	    message(STATUS "Configuring on/for Windows")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
	    message(STATUS "Configuring on/for IBM AIX")
    else()
	    message(STATUS "Configuring on/for ${CMAKE_SYSTEM_NAME}")
    endif()

    ```
13. 处理与平台相关的源代码
    ```cmake
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_compile_definitions(hello-world PUBLIC "IS_LINUX")
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        target_compile_definitions(hello-world PUBLIC "IS_MACOS")
    endif()
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_compile_definitions(hello-world PUBLIC "IS_WINDOWS")
    endif()
    ```
    知道是哪种平台之后可以定义一些宏定义 如上面所示target_compile_definitions(hello-world PUBLIC "IS_LINUX")

14. 编译器相关的
    ```cmake
    target_compile_definitions(hello-world PUBLIC "COMPILER_NAME=\"${CMAKE_CXX_COMPILER_ID}\"")

    if(CMAKE_CXX_COMPILER_ID MATCHES Intel)
        target_compile_definitions(hello-world PUBLIC "IS_INTEL_CXX_COMPILER")
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        target_compile_definitions(hello-world PUBLIC "IS_GNU_CXX_COMPILER")
    endif()
    
    ```
15. 64bit还是32bit的操作系统
    ```cmake
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        target_compile_definitions(arch-dependent PUBLIC "IS_64_BIT_ARCH")
        message(STATUS "Target is 64 bits")
    else()
        target_compile_definitions(arch-dependent PUBLIC "IS_32_BIT_ARCH")
        message(STATUS "Target is 32 bits")
    endif()
    ```
16. 记录项目版本信息
    
    [example](https://github.com/dev-cafe/cmake-cookbook/tree/master/chapter-06/recipe-04/c-example)

17. 