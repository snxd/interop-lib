cmake_minimum_required(VERSION 3.15)

include_directories(.)

set(INTEROPLIB_SRCS
    dictionaryi.h
    interoplib.c
    interoplib.h
    interopstub.h
    taski.h
    workflowi.h)

project(interoplib C)

add_library(${PROJECT_NAME} STATIC ${INTEROPLIB_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
