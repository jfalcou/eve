## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.2)
## -------------------------------------------------------------------------------------------------
## Setup project
## -------------------------------------------------------------------------------------------------
project(eve LANGUAGES CXX)
set(PROJECT_VERSION 1.18.6.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

## -------------------------------------------------------------------------------------------------
## No in-source build
## -------------------------------------------------------------------------------------------------
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[eve]: In-source build is not recommend")
endif()

## -------------------------------------------------------------------------------------------------
## Add include directories
## -------------------------------------------------------------------------------------------------
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/test
  ${PROJECT_SOURCE_DIR}/benchmark
)

## -------------------------------------------------------------------------------------------------
## Install target
## -------------------------------------------------------------------------------------------------
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION .)

## -------------------------------------------------------------------------------------------------
## Test and Benchmarks target
## -------------------------------------------------------------------------------------------------
include(CTest)

## include(benchmark)
include(test)
