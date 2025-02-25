cmake_minimum_required(VERSION 3.5)
project(ThreadDemo)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(threadproj thread.cpp)

target_link_libraries(threadproj Threads::Threads)
