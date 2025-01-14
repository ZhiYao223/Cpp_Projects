cmake_minimum_required (VERSION 2.8)
 
project (learn_lib)

#整合源文件
aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/main_src MAIN_SRC)
# 到指定目录下查找头文件
include_directories(${CMAKE_SOURCE_DIR}/src/include)

#把库链接到可执行文件
target_link_libraries(hello ${FUNC_LIB})

#查找库文件，第二个参数：库的名字，第三个参数：库的路
径
find_library(FUNC_LIB myfunc ${CMAKE_SOURCE_DIR}/lib)

#设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(hello ${MAIN_SRC})
# 生成静态库或动态库，参数一：库的名字，参数二：库的类型，参数三：库的源文件
add_library(func_shared SHARED ${SRC_LIST})
add_library(func_static STATIC ${SRC_LIST})
# 设置库的输出名称,参数一：库的名字，参数二：库的输出名称
set_target_properties(func_shared PROPERTIES OUTPUT_NAME "myfunc")
set_target_properties(func_static PROPERTIES OUTPUT_NAME "myfunc")

#设置库默认生成到哪
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 查找某目录下的所有源文件
aux_source_directory(./src SRC_LIST)

add_executable(hello ${SRC_LIST})
