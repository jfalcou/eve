##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for commit ${GIT_BRANCH}")

# Enable FetchContent
include(FetchContent)

# Retrieve EVE from relative git directory
FetchContent_Declare( eve
                      GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
                      GIT_TAG "${GIT_BRANCH}"
                    )

# make available
FetchContent_MakeAvailable(eve)

add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
add_test(NAME test_eve COMMAND test_eve)
