cmake_minimum_required(VERSION 2.8)

include_directories(.)

set(INTEROPLIB_SRC
    interoplib.c)

set(INTEROPLIB_HEADERS
    dictionaryi.h
    interoplib.h
    interopstub.h
    taski.h
    workflowi.h)

project(interoplib C)

add_library(${PROJECT_NAME} STATIC ${INTEROPLIB_SRC} ${INTEROPLIB_HEADERS})