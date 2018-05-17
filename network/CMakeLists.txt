# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

project (network)

aux_source_directory(. DIR_SRCS)

add_definitions(-std=c++11)

add_library(network ${DIR_SRCS})
