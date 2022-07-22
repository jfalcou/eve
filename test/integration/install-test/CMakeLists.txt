##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-install-test LANGUAGES CXX)
enable_testing()

# pass -D eve_ROOT=path/to-install to cmake if a custom installation prefix was used

find_package(eve CONFIG REQUIRED)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
