##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-install-test LANGUAGES CXX)

message(STATUS "Testing FetchContent for branch ${EVE_SHA1}")

# Setup CPM
include(cpm.cmake)

# Add dependencies
CPMAddPackage ( NAME eve
                GITHUB_REPOSITORY jfalcou/eve
                GIT_TAG ${EVE_SHA1}
                OPTIONS "EVE_BUILD_TEST OFF"
                        "EVE_BUILD_BENCHMARKS OFF"
                        "EVE_BUILD_DOCUMENTATION OFF"
              )

# Use EVE
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
