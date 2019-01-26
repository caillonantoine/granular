cmake_minimum_required(VERSION 3.0)

project(GRANULAR)

file(GLOB SRC src/*.cpp)

add_library(granular SHARED ${SRC})
set_target_properties(granular PROPERTIES PREFIX "" SUFFIX "~.pd_linux")
