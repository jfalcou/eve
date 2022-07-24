##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-install-test LANGUAGES CXX)
enable_testing()

find_package(eve CONFIG REQUIRED)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC ${EVE_LIBRARIES})
add_test(NAME test_eve COMMAND test_eve)
