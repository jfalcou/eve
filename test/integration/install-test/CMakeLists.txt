##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.18)
project(eve-install-test LANGUAGES CXX)
enable_testing()

<<<<<<< HEAD
find_package(eve CONFIG REQUIRED)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC ${EVE_LIBRARIES})
add_test(NAME test_eve COMMAND test_eve)
=======
# pass -D eve_ROOT=path/to-install to cmake if a custom installation prefix was used

find_package(eve CONFIG REQUIRED)
add_executable(test_eve ../main.cpp)
target_link_libraries(test_eve PUBLIC eve::eve)
>>>>>>> 09af54f82 (update install test's cmake w/ new target)
