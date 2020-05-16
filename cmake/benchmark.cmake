##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(download)
include(generate_benchmark)
include(add_parent_target)

##==================================================================================================
## Common variables
##==================================================================================================
set(_BenchCurrentDir "${CMAKE_CURRENT_LIST_DIR}")
set(_BenchSrcDir     "${PROJECT_BINARY_DIR}/tmp-src")

##==================================================================================================
## Setup a basic test
##==================================================================================================
function(make_bench root)
  foreach(file ${ARGN})
    generate_test(${root} "" "" ${file})
  endforeach()
endfunction()

##==================================================================================================
## Generate a complete family of test
##==================================================================================================
function(make_all_benchs)
  # Parse our options to find name, arch and types to generate
  set(multiValueArgs TYPES ARCH)
  set(oneValueArgs ROOT NAME CARDINAL)
  cmake_parse_arguments(GEN_TEST "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  # Locate all subdirectory for current test
  file(GLOB locations "${GEN_TEST_NAME}/*")

  # Generate tests for each variant location
  foreach( variant ${locations})

    # header to include in autogen tests
    set(header "${variant}/${GEN_TEST_NAME}")

    if(EXISTS "${header}.hpp")

      # Locate relative path for simpler autogen file paths
      file(RELATIVE_PATH base_file ${CMAKE_CURRENT_SOURCE_DIR} ${variant})

      # Generate test for each arch
      foreach( arch ${GEN_TEST_ARCH})
        # Scalar case just uses the types as setup
        if( arch STREQUAL scalar)
          foreach(type ${GEN_TEST_TYPES})
            to_std("${type}" target)
            set(file_to_compile "${_BenchSrcDir}/bench/${GEN_TEST_ROOT}.${base_file}.scalar.${type}.cpp")

            configure_file( "${_BenchCurrentDir}/bench.scalar.cpp.in" "${file_to_compile}" )
            generate_bench( "" "${_BenchSrcDir}/bench/" "${GEN_TEST_ROOT}.scalar.bench"
                            "${GEN_TEST_ROOT}.${base_file}.scalar.${type}.cpp"
                          )
          endforeach()
        endif()

        # SIMD case uses the types x cardinals as setup
        if( arch STREQUAL simd)
          foreach(type ${GEN_TEST_TYPES})
            to_std("${type}" target)
            set(file_to_compile "${_BenchSrcDir}/bench/${GEN_TEST_ROOT}.${base_file}.simd.${type}.cpp")

            configure_file( "${_BenchCurrentDir}/bench.simd.cpp.in" "${file_to_compile}" )

            generate_bench( "" "${_BenchSrcDir}/bench/" "${GEN_TEST_ROOT}.simd.bench"
                            "${GEN_TEST_ROOT}.${base_file}.simd.${type}.cpp"
                          )
          endforeach()
        endif()
      endforeach()
    endif()

  endforeach()
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


##==================================================================================================
## Setup our tests
##==================================================================================================
add_custom_target(bench)

add_subdirectory(${PROJECT_SOURCE_DIR}/benchmarks/)
