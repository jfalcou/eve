##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(target/generate_test)
include(target/failure)

##==================================================================================================
## Basic type roots
##==================================================================================================
set(real_types         double float                            )
set(int_types          int64 int32 int16 int8                  )
set(uint_types         uint64 uint32 uint16 uint8              )
set(integral_types     "${int_types};${uint_types}"            )
set(all_types          "${real_types};${integral_types}"       )
set(signed_types       "${real_types};${int_types}"            )
set(real_types_32      float                                   )
set(int_types_32       int32 int16 int8                        )
set(uint_types_32      uint32 uint16 uint8                     )
set(integral_types_32  "${int_types_32};${uint_types_32}"      )
set(all_types_32       "${real_types_32};${integral_types_32}" )
set(signed_types_32    "${real_types_32};${int_types_32}"      )
set(uint_or_real_types "${real_types};${uint_types}"           )
set(uint_or_real_types_32 "${real_types_32};${uint_types_32}"  )

macro(to_std type output)
  if(${type} MATCHES "^[u]?int[a-zA-Z]*")
    set(${output} "std::${type}_t")
  else()
    set(${output} "${type}")
  endif()
endmacro()

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

          configure_file( "${${CMAKE_CURRENT_LIST_DIR}}/scalar.cpp.in" "${file_to_compile}" )

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

          configure_file( "${${CMAKE_CURRENT_LIST_DIR}}/simd.cpp.in" "${file_to_compile}" )

          generate_test ( "" "${_TestSrcDir}/" "${GEN_TEST_ROOT}.simd.exe"
                          "${GEN_TEST_ROOT}.${base_file}.simd.cpp"
                        )

        endif()
      endforeach()
    endif()

  endforeach()
endfunction()
