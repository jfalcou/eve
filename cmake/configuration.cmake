##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2020 Joel FALCOU
##  Copyright 2018-2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Find Boost
##==================================================================================================
find_package(Boost 1.65.0 QUIET)

if(Boost_FOUND)
  set(EVE_USE_BOOST 1)
  message( STATUS "[eve] Boost found in ${Boost_INCLUDE_DIRS} - Boost dependent tests activated")
  string(REPLACE "/usr/include" "" Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
else()
  set(Boost_INCLUDE_DIRS "")
endif()

##==================================================================================================
## Gathering compiler options
##==================================================================================================
add_library(eve_test INTERFACE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( eve_test INTERFACE /W3 /EHsc /std:c++latest)
else()
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wall -Wpedantic -Wextra)
endif()

##==================================================================================================
## Setup TTS
##==================================================================================================
set(TTS_BUILD_TEST    OFF CACHE INTERNAL "OFF")
set(TTS_IS_DEPENDENT  ON  CACHE INTERNAL "ON")

include(FetchContent)
FetchContent_Declare( tts
                      GIT_REPOSITORY https://github.com/jfalcou/tts.git
                      GIT_TAG main
                    )

FetchContent_MakeAvailable(tts)
