#要求cmake工具最低版本
cmake_minimum_required(VERSION 3.16)
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
include_directories(src/function)

#如果有子CMakeFile文件
#add_subdirectory(src/function)

#控制多个可执行文件
add_executable(main src/main.c)
add_executable(main_function src/function/main.c)