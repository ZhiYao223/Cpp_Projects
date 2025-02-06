cmake_minimum_required(VERSION 3.16)
project(NetworkTest)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

#添加可执行文件
add_executable(servertest servertest.cpp)
add_executable(clienttest clienttest.cpp)

#自定义目标来运行服务器
add_custom_target(run_server
    COMMAND ./servertest 5005
    DEPENDS servertest
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
# 自定义目标来运行客户端
add_custom_target(run_client
    COMMAND ./clienttest 192.168.206.128 5005
    DEPENDS clienttest
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
