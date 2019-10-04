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

if(WIN32)
    set(CMAKE_C_FLAGS_DEBUG "/MTd")
    set(CMAKE_C_FLAGS_RELEASE "/MT")
    set(CMAKE_C_FLAGS_MINSIZEREL "/MT")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT")
endif()

project(interoplib C)

add_library(${PROJECT_NAME} STATIC ${INTEROPLIB_SRC} ${INTEROPLIB_HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)