##======================================================================================================================
##  EVE - Compact C++20 Tuple Toolbox
##  Copyright : eve Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-cpm-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing CPM for branch ${GIT_BRANCH}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME eve
                GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
                GIT_TAG "${GIT_BRANCH}"
                OPTIONS "EVE_BUILD_TEST OFF"
              )

# Use eve
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
add_test(NAME test_eve COMMAND test_eve)
