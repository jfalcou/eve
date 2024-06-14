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
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wall -Wpedantic -Wextra)
else()
  target_compile_options( eve_test INTERFACE -std=c++20 -Werror -Wall -Wpedantic -Wextra -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow)
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
