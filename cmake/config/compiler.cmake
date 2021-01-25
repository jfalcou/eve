##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Gathering compiler options
##==================================================================================================
add_library(eve_test INTERFACE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( eve_test INTERFACE /W3 /EHsc /std:c++latest)
else()
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wall -Wpedantic -Wextra)
endif()

target_include_directories( eve_test INTERFACE
                            ${tts_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                            ${Boost_INCLUDE_DIRS}
                          )
