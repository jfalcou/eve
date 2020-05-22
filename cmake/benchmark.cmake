##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

include(download)
include(add_parent_target)

##==================================================================================================
## Centralize all required setup for unit benchs
##==================================================================================================
function(add_bench root)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set( _BenchOptions -std=c++20 -Wall)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set( _BenchOptions -std=c++20 -Wall)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set( _BenchOptions /std:c++latest -W3 -EHsc)
endif()

  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".bench" base ${file})
    string(REPLACE "/"    "." base ${base})
    string(REPLACE "\\"   "." base ${base})
    set(bench "${root}.${base}")

    add_executable( ${bench}  ${file})
    target_compile_options  ( ${bench} PUBLIC ${_BenchOptions} )

    set_property( TARGET ${bench}
                  PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bench"
                )

    add_test( NAME ${bench}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/bench"
              COMMAND $<TARGET_FILE:${bench}> --benchmark_counters_tabular=true --benchmark_repetitions=3  --benchmark_report_aggregates_only=true
            )

    set_target_properties ( ${bench} PROPERTIES
                            EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            EXCLUDE_FROM_ALL TRUE
                            ${MAKE_UNIT_TARGET_PROPERTIES}
                          )

    target_include_directories( ${bench}
                                PRIVATE
                                  ${tts_SOURCE_DIR}/include
                                  ${googlebenchmark_SOURCE_DIR}/include
                                  ${googlebenchmark_SOURCE_DIR}/src
                                  ${PROJECT_SOURCE_DIR}/benchmark
                                  ${PROJECT_SOURCE_DIR}/include
                                  ${Boost_INCLUDE_DIRS}
                              )

    target_link_libraries(${bench} benchmark)
    add_dependencies(bench ${bench})

    add_parent_target(${bench})
  endforeach()
endfunction()

##==================================================================================================
## Generate a list of benchs from a type list
##==================================================================================================
function (list_benchs root bench)
  set(sources )

  foreach(e ${ARGN})
    list(APPEND sources "${root}/${e}.cpp")
  endforeach(e)

  add_bench( ${bench} "${sources}" )
endfunction()

##==================================================================================================
## Disable benching/doc for Google Bench
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")

download_project( PROJ                googlebenchmark
                  GIT_REPOSITORY      https://github.com/google/benchmark.git
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})

## Setup our benchs
add_custom_target(bench)

add_subdirectory(${PROJECT_SOURCE_DIR}/benchmark/)
