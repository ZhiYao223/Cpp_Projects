cmake_minimum_required(VERSION 3.16) 
project(Cmakeproj) 
# 添加宏定义,在源文件中可以使用#ifdef DEBUG ... #endif来判断是否定义了DEBUG
add_definitions(-DDEBUG) 
aux_source_directory(${PROJECT_SOURCE_DIR} HOME)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/inc)
# 静态库生成的路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行程序的存储目录
set(EXECPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件的存储目录
set(HEADPATH ${PROJECT_SOURCE_DIR}/inc)

#库文件的名字
set(CALCLIB calc)
set(SORTLIB sort)
#可执行程序的名字
set(APPNAME1 app1)
set(APPNAME2 app2)
#给当前节点添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)

# 添加源文件到编译列表,该函数不可用于添加头文件inc下的.h文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)



# 设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件app
add_executable(app ${SRC_LIST}) 










