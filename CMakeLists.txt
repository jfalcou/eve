##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
enable_testing()

## =================================================================================================
## Setup project
## =================================================================================================
project(eve LANGUAGES CXX)

set(EVE_MAJOR_VERSION 2022)
set(EVE_MINOR_VERSION 3)
set(EVE_PATCH_VERSION 0)
set(EVE_VERSION ${EVE_MAJOR_VERSION}.${EVE_MINOR_VERSION}.${EVE_PATCH_VERSION})

set(PROJECT_VERSION   ${EVE_VERSION})
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
include(config/eve-install)

## =================================================================================================
## Documentation target
## =================================================================================================
if( EVE_BUILD_DOCUMENTATION )
  include(config/doxygen)
endif()

## =================================================================================================
## Test and Benchmarks target
## =================================================================================================
if( EVE_BUILD_TEST )
  include(config/dependencies)
  include(CTest)
  include(target/add_parent_target)
  include(config/compiler)
  include(config/types)
  include(config/pch)

  include(target/targets)
  add_subdirectory("${PROJECT_SOURCE_DIR}/test/")
  add_subdirectory("${PROJECT_SOURCE_DIR}/examples/")
endif()

if( EVE_BUILD_INTEGRATION )
  add_subdirectory("${PROJECT_SOURCE_DIR}/test/integration")
endif()

if( EVE_BUILD_BENCHMARKS )
  add_subdirectory("${PROJECT_SOURCE_DIR}/benchmarks/")
endif()
