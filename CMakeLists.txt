#要求cmake工具最低版本
cmake_minimum_required(VERSION 3.13)
#设置变量
#set(变量名 值1 值2 ...)

#取变量值
#${变量名}

#设置宏定义
#ADD_DEFINITIONS("-D宏名 -D宏名")
#ADD_DEFINITIONS(-D宏名)
#ADD_DEFINITIONS(-D宏名 -D宏名)

#设置项目名称
project(c_learn)
#设置项目可执行文件目标输出文件

#set(EXECUTEABLE_OUTPUT_PATH 目录)
set(CMAKE_C_STANDARD 99)

#头文件引用路径：
include_directories(function pthread)

#如果有子CMakeFile文件
#add_subdirectory(function)

set(SOURCE_TMP function/function.c pthread/thread.c )
#控制多个可执行文件（可以添加多个）
add_executable(main main.c ${SOURCE_TMP})
add_executable(thread_main pthread/thread_main.c ${SOURCE_TMP})
add_executable(test_main test/test_main.c ${SOURCE_TMP})
add_executable(server_main network/serverSocket.c)
add_executable(client_main network/clientSocket.c)
#add_executable(main1 main1.c ${SOURCE_TMP})
#add_executable(main1 main2.c ${SOURCE_TMP})

#给上面对应的main添加 pthread引用库，如果不添加，pthread为找不到
find_package(Threads)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thread_main ${CMAKE_THREAD_LIBS_INIT})