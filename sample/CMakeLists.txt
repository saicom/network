# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

include_directories(../network)

link_directories(../network)

project (test_network)

aux_source_directory(. DIR_SRCS)

set(LIBS  -lpthread
	   libnetwork.a
)

add_definitions("-Wall -g -m64 -std=c++11")

add_executable(test ${DIR_SRCS})

target_link_libraries(test ${LIBS})
