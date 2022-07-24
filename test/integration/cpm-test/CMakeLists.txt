##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-cpm-test LANGUAGES CXX)

message(STATUS "Testing CPM for commit ${eve_git_head}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME eve
                GIT_REPOSITORY "${eve_SOURCE_DIR}"
                GIT_TAG "${eve_git_head}"
                OPTIONS "EVE_BUILD_TEST OFF"
                        "EVE_BUILD_BENCHMARKS OFF"
                        "EVE_BUILD_DOCUMENTATION OFF"
              )

# Use EVE
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
