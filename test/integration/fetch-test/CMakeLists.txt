##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-fetch-test LANGUAGES CXX)

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
