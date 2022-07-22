##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-install-test LANGUAGES CXX)

message(STATUS "Testing FetchContent for branch ${EVE_SHA1}")

# Enable FetchContent
include(FetchContent)

# Retrieve EVE
FetchContent_Declare(eve
  GIT_REPOSITORY "https://github.com/jfalcou/eve.git"
  GIT_TAG        "$ENV{GITHUB_SHA}"
  )

FetchContent_MakeAvailable(eve)

# make available
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
