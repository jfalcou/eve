##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.19)
project(eve-install-test LANGUAGES CXX)

## Points to the installation folder for EVE
set(CMAKE_PREFIX_PATH "/usr/local/lib")

find_package(eve)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC ${EVE_LIBRARIES})
