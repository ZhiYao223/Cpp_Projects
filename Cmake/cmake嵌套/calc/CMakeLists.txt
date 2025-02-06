cmake_minimum_required(VERSION 3.16)
project(calc)
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
include_directories(${k}/inc)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)




















add_library(${SORTLIB} STATIC ${SRC})
