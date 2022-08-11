##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-cpm-test LANGUAGES CXX)
enable_testing()

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
add_test(NAME test_eve COMMAND test_eve)
