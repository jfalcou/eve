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

## =================================================================================================
## No in-source build
## =================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message( FATAL_ERROR "[eve] Building in-source, not recommended! Build in a separate directory." )
endif()

## =================================================================================================
## Configuration
## =================================================================================================
include(config/options)
include(config/install)

## =================================================================================================
## Test and Benchmarks target
## =================================================================================================
if( EVE_BUILD_TEST )
add_subdirectory(test)
endif()
