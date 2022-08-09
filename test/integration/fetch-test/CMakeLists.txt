##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-fetch-test LANGUAGES CXX)
enable_testing()

message(STATUS "Testing FetchContent for commit ${eve_git_head}")

# Enable FetchContent
include(FetchContent)

# Retrieve EVE from relative git directory
FetchContent_Declare(eve
  GIT_REPOSITORY "${eve_SOURCE_DIR}"
  GIT_TAG "${eve_git_head}"
)

# make available
FetchContent_MakeAvailable(eve)

add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
add_test(NAME test_eve COMMAND test_eve)
