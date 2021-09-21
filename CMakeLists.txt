##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
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
include(config/dependencies)

## =================================================================================================
## Documentation target
## =================================================================================================
if( EVE_BUILD_DOCUMENTATION )
  include(config/doxygen)
endif()

## =================================================================================================
## Test and Benchmarks target
## =================================================================================================
include(CTest)
include(target/add_parent_target)
include(target/targets)
include(config/compiler)
include(config/types)
include(config/pch)

if( EVE_BUILD_TEST )
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
  add_subdirectory(${PROJECT_SOURCE_DIR}/examples/)
endif()

if( EVE_BUILD_BENCHMARKS )
  add_subdirectory(${PROJECT_SOURCE_DIR}/benchmarks/)
endif()
