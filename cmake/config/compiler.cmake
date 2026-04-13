##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Gathering compiler options for unit tests
##==================================================================================================
add_library(eve_test INTERFACE)

target_compile_features ( eve_test INTERFACE cxx_std_20 )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options( eve_test INTERFACE /bigobj /EHsc /W3 /wd4244 /wd4267 /wd4146 /utf-8 /WX )
  else()
    target_compile_options( eve_test INTERFACE -Werror -Wshadow -Wall -Wpedantic -Wextra -fcolor-diagnostics
                            -ftemplate-backtrace-limit=0
                          )
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( eve_test INTERFACE /bigobj /EHsc /W3 /utf-8 /wd4244 /wd4267 /wd4146 /wd4018 /wd4305 /wd4334 /WX /Zc:preprocessor ) 
else()
  target_compile_options( eve_test INTERFACE  -Werror -Wshadow -Wall -Wpedantic -Wextra -fdiagnostics-color=always
                          -ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=8
                          -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow
                          -Wno-maybe-uninitialized
                        )
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

target_compile_features ( eve_bench INTERFACE  cxx_std_20 )

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options( eve_bench INTERFACE /0x /W3 /EHsc )
else()
  target_compile_options( eve_bench INTERFACE -O3 -Werror -Wall -Wpedantic -Wextra)
endif()

target_include_directories( eve_bench INTERFACE
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/examples
                            ${PROJECT_SOURCE_DIR}/include
                          )

target_include_directories( eve_bench SYSTEM INTERFACE
                            ${Boost_INCLUDE_DIRS}
                          )
