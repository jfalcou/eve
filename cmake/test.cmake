##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(target/generate_test)

set(_TestCurrentDir "${CMAKE_CURRENT_LIST_DIR}")
set(_TestSrcDir      "${PROJECT_BINARY_DIR}/tmp-src")

##==================================================================================================
## Generate a complete family of test
##==================================================================================================
function(make_all_units)
  # Parse our options to find name, arch and types to generate
  set(multiValueArgs TYPES ARCH)
  set(oneValueArgs ROOT NAME)
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
        list(SUBLIST GEN_TEST_TYPES 0  1 head)
        list(SUBLIST GEN_TEST_TYPES 1 -1 tail)

        # Scalar case just uses t1he types as setup
        if( arch STREQUAL scalar)

          to_std("${head}" target)
          foreach(type ${tail})
            to_std("${type}" name)
            string(JOIN "," target "${target}" "${name}")
          endforeach()

          set(file_to_compile "${_TestSrcDir}/${GEN_TEST_ROOT}.${base_file}.scalar.cpp")

          configure_file( "${_TestCurrentDir}/scalar.cpp.in" "${file_to_compile}" )

          generate_test ( "" "${_TestSrcDir}/" "${GEN_TEST_ROOT}.scalar.exe"
                          "${GEN_TEST_ROOT}.${base_file}.scalar.cpp"
                        )
        endif()

        # SIMD case uses the types x cardinals as setup
        if( arch STREQUAL simd)

          if( EVE_TEST_TYPE )
          set( base "${EVE_TEST_TYPE}")
          else()
          set( base "eve::wide")
          endif()

          to_std("${head}" target)
          set(target "${base}<${target}>")
          foreach(type ${tail})
            to_std("${type}" name)
            string(JOIN "," target "${target}" "${base}<${name}>")
          endforeach()

          set(file_to_compile "${_TestSrcDir}/${GEN_TEST_ROOT}.${base_file}.simd.cpp")

          configure_file( "${_TestCurrentDir}/simd.cpp.in" "${file_to_compile}" )

          generate_test ( "" "${_TestSrcDir}/" "${GEN_TEST_ROOT}.simd.exe"
                          "${GEN_TEST_ROOT}.${base_file}.simd.cpp"
                        )

        endif()
      endforeach()
    endif()

  endforeach()
endfunction()
