##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-install-test LANGUAGES CXX)
enable_testing()

# pass -D eve_ROOT=path/to-install to cmake if a custom installation prefix was used

find_package(eve CONFIG REQUIRED)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
add_test(NAME test_eve COMMAND test_eve)
