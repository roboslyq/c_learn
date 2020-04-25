[CMake] cmake入门: 调用多个目录下的源文件
原创 Sthnnnnn 最后发布于2020-02-27 17:53:55 阅读数 92 收藏
展开
CMake入门
举例一：

假设工程HelloWorld文件结构如下:
-main.cpp
-MyClass/
–MyClass.h
–MyClass.cpp
在main.cpp中include<MyClass.h>
方法一 在根目录下的CMakeLists.txt内容为:

cmake_minimum_required(VERSION 3.12)
project(HelloWorld)
set(CMAKE_CXX_STANDARD 14)  
# 包含进目录 MyClass/  
include_directories("${PROJECT_SOURCE_DIR}"/MyClass)  
# 使用指定文件生成可执行文件 HelloWorld  
add_executable(HelloWorld main.cpp MyClass/MyClass.h MyClass.cpp)  

    1
    2
    3
    4
    5
    6
    7

该方法为直接使用全部的资源文件生层可执行文件
方法二 在根目录下的CMakeLists.txt为:

cmake_minimum_required(VERSION 3.15)
project(HelloWorld)
set(CMAKE_CXX_STANDARD 14)
# 搜集指定目录 . 和./MyClass 下的源文件，将输出结果列表储存到变量ALL_SOURCE中
aux_source_directory(. ALL_SOURCE)
aux_source_directory(${PROJECT_SOURCE_DIR}/MyClass ALL_SOURCE)
# 包含进目录 MyClass/
include_directories("${PROJECT_SOURCE_DIR}/MyClass")
# 使用指定文件生成可执行文件 HelloWorld
add_executable(HelloWorld ${ALL_SOURCE})

    1
    2
    3
    4
    5
    6
    7
    8
    9
    10

该方法同为直接使用全部的资源文件，但是这次使用aux_source_directory()命令自动收集参数目录下的全部源文件到变量中，在这个例子中看起来似乎比方法一复杂，但是对于目录下有很多源文件的情况比方法一简单。
方法三 在MyClass/和根目录下分别建立CMakeLists.txt文件:

根目录下的CMakeLists.txt为:

cmake_minimum_required(VERSION 3.15)
project(HelloWorld)
set(CMAKE_CXX_STANDARD 14)
# 添加子目录 MyClass/ 并且也会处理 MyClass目录下的 CMakeLists.txt文件
add_subdirectory(MyClass)
# 包含进目录 MyClass/
include_directories("${PROJECT_SOURCE_DIR}/MyClass")
# 生成可执行文件 HelloWorld
add_executable(HelloWorld main.cpp)
# 将可执行文件添加链接库 MyClass
target_link_libraries(HelloWorld MyClass)

    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11

MyClass/目录下CMakeLists.txt为:

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)
#搜集MyClass目录下的文件
aux_source_directory(. MYCLASS_SOURCE)
#生成链接库
add_library(MyClass ${MYCLASS_SOURCE})

    1
    2
    3
    4
    5
    6

该方法将MyClass目录下的源文件生成一个静态链接库，在生成可执行文件之后将可执行文件与链接库文件链接起来运行。比方法一、二更合理（我觉得）。
举例二：

假设工程HelloWorld文件结构如下:
-main.cpp
-MyClass/
–MyClass.h
–MyClass.cpp
-MyFunction/
–MyFunction.h
–MyFunction.cpp
在main.cpp中 #include<MyFunction.h>
在MyFunction.cpp中 #include<MyClass.h>
方法一 在根目录下、MyClass目录和MyFunction目录下都新建CMakeLists.txt文件

根目录下CMakeLists.txt为:

cmake_minimum_required(VERSION 3.15)
project(HelloWorld)
set(CMAKE_CXX_STANDARD 14)
#添加子目录 MyClass/ 并且也会处理 MyClass目录下的 CMakeLists.txt文件
add_subdirectory(MyClass)
add_subdirectory(MyFunction)
#生成可执行文件 HelloWorld
add_executable(HelloWorld main.cpp)
#将可执行文件添加链接库MyFunction
target_link_libraries(HelloWorld MyFunction)
#将目录MyFunction添加到HelloWorld目标路径中
target_include_directories(HelloWorld PUBLIC MyFunction)

    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    11
    12

在MyClass目录下的CMakeLists.txt文件为:

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)
#搜集MyClass目录下的文件
aux_source_directory(. MYCLASS_SOURCE)
#生成链接库
add_library(MyClass ${MYCLASS_SOURCE})

    1
    2
    3
    4
    5
    6

在MyFunction目录下的CMakeLists.txt文件为:

 cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
#生成链接库
add_library(MyFunction MyFunction.h MyFunction.cpp)
#目标链接库MyFunction添加链接库MyClass
target_link_libraries(MyFunction MyClass)
#将目录MyClass添加的目标目录中
target_include_directories(MyFunction PUBLIC ../MyClass)

    1
    2
    3
    4
    5
    6
    7
    8

同时另外提一点，根目录下的CMakeLists.txt文件中的命令include_directories()是用来将目录MyClass/添加到编译器搜索包含文件的路径列表中，这样在main.cpp文件中可以使用#include<MyClass.h>。如果没有include_directoris()命令，必须在main.c中使用#include<MyClass/MyClass.h>包含头文件。
————————————————
版权声明：本文为CSDN博主「Sthnnnnn」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Strengthennn/java/article/details/104540673