##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Gathering compiler options for unit tests
##==================================================================================================
add_library(eve_test INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( eve_test INTERFACE /bigobj /W3 /EHsc /std:c++20 /wd4267 /wd4244 /wd4146)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wshadow -Wall -Wpedantic -Wextra -fcolor-diagnostics)
else()
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wshadow -Wall -Wpedantic -Wextra -fdiagnostics-color=always
                          -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow
                          -Wno-maybe-uninitialized
                        )
endif()

if(EVE_ENABLE_COVERAGE)
  if(CMAKE_BUILD_TYPE MATCHES "Release")
    message(FATAL_ERROR "EVE coverage profiling is not supported in Release mode")
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(FATAL_ERROR "EVE coverage profiling is not yet supported on MSVC")
  else()
    target_compile_options( eve_test INTERFACE --coverage -fprofile-update=atomic -fno-inline -fno-inline-small-functions -fno-default-inline )
    target_link_options( eve_test INTERFACE --coverage )
  endif()
endif()

target_include_directories( eve_test INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/examples
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_include_directories( eve_test SYSTEM INTERFACE
                            ${Boost_INCLUDE_DIRS}
                          )

##==================================================================================================
## Gathering compiler options for Benchmarks
##==================================================================================================
add_library(eve_bench INTERFACE)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( eve_bench INTERFACE /0x /W3 /EHsc /std:c++latest)
else()
  target_compile_options( eve_bench INTERFACE -O3 -std=c++20 -Werror -Wall -Wpedantic -Wextra)
endif()

target_include_directories( eve_bench INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/examples
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_include_directories( eve_bench SYSTEM INTERFACE
                            ${Boost_INCLUDE_DIRS}
                          )
