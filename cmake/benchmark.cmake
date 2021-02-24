##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(target/generate_benchmark)

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
    generate_test(${root} "" "" ${file} )
  endforeach()
endfunction()

##==================================================================================================
## Generate a complete family of test
##==================================================================================================
function(make_all_benchs)
  # Parse our options to find name, arch and types to generate
  set(multiValueArgs TYPES)
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
      foreach(type ${GEN_TEST_TYPES})
        to_std("${type}" target)

        set(file_to_compile "${_BenchSrcDir}/bench/${GEN_TEST_ROOT}.${base_file}.${type}.cpp")

        configure_file( "${_BenchCurrentDir}/bench.cpp.in" "${file_to_compile}" )

        generate_bench( "" "${_BenchSrcDir}/bench/" "${GEN_TEST_ROOT}.exe"
                        "${GEN_TEST_ROOT}.${base_file}.${type}.cpp"
                      )

      endforeach()
    endif()

  endforeach()
endfunction()

##==================================================================================================
## Setup our tests
##==================================================================================================
add_custom_target(bench)
