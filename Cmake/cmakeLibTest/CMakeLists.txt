cmake_minimum_required(VERSION 3.16) 
project(Cmakeproj)
aux_source_directory(${PROJECT_SOURCE_DIR} HOME)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/inc)

#include_directories(${PROJECT_SOURCE_DIR}/src) # 该行多余，可删除，因为src目录下的头文件不需要被引用

# 添加源文件到编译列表,该函数不可用于添加头文件inc下的.h文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# 生成动态库,如果要生存静态库，将SHARED改为STATIC
add_library(OurLib SHARED ${SRC_LIST})

# 设置动态库文件输出位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置链接库
link_libraries(OurLib)
link_libraries(libOurLib.so)
# 指定库文件搜索路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 设置编译选项
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件app
add_executable(appstatic ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# 如果使用静态库，在生成可执行程序时，静态库和对应的源文件都会被打包到可执行文件appstatic中
# 如果使用动态库，在生成可执行程序时，动态库不会被打包到可执行文件appshared中








