##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
## =================================================================================================
## Setup project
## =================================================================================================
project(eve LANGUAGES CXX)
set(PROJECT_VERSION 1.20.5.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )

## =================================================================================================
## No in-source build
## =================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[eve] Building in-source, not recommended! Build in a separate directory." )
endif()

## =================================================================================================
## Options
## =================================================================================================
option( EVE_BUILD_TEST        "Build unit tests for eve"                      ON  )
option( EVE_BUILD_RANDOM      "Build random precision tests for eve"          OFF )
option( EVE_BUILD_BENCHMARKS  "Build benchmarks for eve"                      OFF )
option( EVE_BUILD_SRC_HTML    "Convert source to html for eve documentation"  OFF )

if( EVE_BUILD_TEST )
  set(test_status "ON")
else()
  set(test_status "OFF")
endif()

if( EVE_BUILD_RANDOM )
  set(random_status "ON")
else()
  set(random_status "OFF")
endif()

if( EVE_BUILD_BENCHMARKS )
  set(bench_status "ON")
else()
  set(bench_status "OFF")
endif()

if( EVE_BUILD_SRC_HTML )
  set(html_status "ON")
else()
  set(html_status "OFF")
endif()

message( STATUS "[eve] Building ${CMAKE_BUILD_TYPE} mode with: ${CMAKE_CXX_FLAGS}")
message( STATUS "[eve] Unit tests         : ${test_status} (via EVE_BUILD_TEST)"        )
message( STATUS "[eve] Random tests       : ${random_status} (via EVE_BUILD_RANDOM)"    )
message( STATUS "[eve] Benchmarks tests   : ${bench_status} (via EVE_BUILD_BENCHMARKS)" )
message( STATUS "[eve] Source generation  : ${html_status} (via EVE_BUILD_SRC_HTML)"    )

## =================================================================================================
## Install target
## =================================================================================================
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION .)

## =================================================================================================
## Exporting atrget for external use
## =================================================================================================
add_library(eve_lib INTERFACE)
target_include_directories(eve_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_features(eve_lib INTERFACE cxx_std_20)
add_library(eve::eve ALIAS eve_lib)

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
