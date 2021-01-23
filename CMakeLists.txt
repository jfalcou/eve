##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2020 Joel FALCOU
##  Copyright 2018-2020 Jean-Thierry LAPRESTE
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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## =================================================================================================
## No in-source build
## =================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[eve] Building in-source, not recommended! Build in a separate directory." )
endif()

## =================================================================================================
## Options
## =================================================================================================
include(config/options)

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
