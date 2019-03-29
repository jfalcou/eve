##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
## =================================================================================================
## Setup project
## =================================================================================================
project(eve LANGUAGES CXX)
set(PROJECT_VERSION 1.18.6.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

## =================================================================================================
## No in-source build
## =================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[eve] Building in-source, not recommended! Build in a separate directory." )
endif()

## =================================================================================================
## Compute version string and mode
## =================================================================================================
include(parse_revision)

## =================================================================================================
## Options
## =================================================================================================
option( EVE_BUILD_TEST        "Build tests for eve"         ON )
option( EVE_BUILD_BENCHMARKS  "Build benchmarks for eve"    ON )
option( EVE_BUILD_DOC         "Build documentation for eve" ON )

message( STATUS "[eve] Building ${CMAKE_BUILD_TYPE} mode with: ${CMAKE_CXX_FLAGS}")

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION .)

## =================================================================================================
## Setup Documentation
## =================================================================================================
if( EVE_BUILD_TEST )
  add_subdirectory(doc)
endif()

## =================================================================================================
## Test and Benchmarks target
## =================================================================================================
include(CTest)

if( EVE_BUILD_TEST )
  include(test)
endif()

if( EVE_BUILD_BENCHMARKS )
  include(benchmark)
endif()
