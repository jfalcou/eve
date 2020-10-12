##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(generate_test)
include(add_parent_target)

##==================================================================================================
## Common variables
##==================================================================================================
set(_TestCurrentDir "${CMAKE_CURRENT_LIST_DIR}")
set(_TestSrcDir     "${PROJECT_BINARY_DIR}/tmp-src")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set( _TestOptions -std=c++20 -Wall -Werror=unused-parameter)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set( _TestOptions -std=c++20 -Wall -Werror=unused-parameter)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set( _TestOptions /std:c++latest -W3 -EHsc)
endif()

message( STATUS "[eve] Compiler base options: ${_TestOptions}")

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
## Setup a basic test
##==================================================================================================
function(make_unit root)
  foreach(file ${ARGN})
    generate_test(${root} "" "" ${file} "")
  endforeach()
endfunction()

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

          get_property(precompiled_target GLOBAL PROPERTY precompiled_test)

          if ("${precompiled_target}" STREQUAL "")
            set(precompiled_target "GENERATE")
          endif()

          generate_test ( "" "${_TestSrcDir}/" "${GEN_TEST_ROOT}.scalar.exe"
                          "${GEN_TEST_ROOT}.${base_file}.scalar.cpp"
                          "${precompiled_target}"
                        )
          if (NOT ${precompiled_target} STREQUAL "GENERATE")
            set_property(GLOBAL PROPERTY precompiled_test ${precompiled_target})
          endif()
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

          if ("${precompiled_target}" STREQUAL "")
            set(precompiled_target "GENERATE")
          endif()

          generate_test ( "" "${_TestSrcDir}/" "${GEN_TEST_ROOT}.simd.exe"
                          "${GEN_TEST_ROOT}.${base_file}.simd.cpp"
                           "${precompiled_target}"
                        )

          if (NOT ${precompiled_target} STREQUAL "GENERATE")
            set_property(GLOBAL PROPERTY precompiled_test ${precompiled_target})
          endif()

        endif()
      endforeach()
    endif()

  endforeach()
endfunction()

##==================================================================================================
## Create a test that succeed if its compilation fails
##==================================================================================================
function(check_failure root)
  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".exe" base ${file})
    string(REPLACE "/"    "." base ${base})
    string(REPLACE "\\"   "." base ${base})
    set(test "${root}.${base}")

    set( test_lib "${test}_lib")
    add_library( ${test_lib} OBJECT EXCLUDE_FROM_ALL ${file})
    target_compile_options  ( ${test_lib} PUBLIC ${_TestOptions} )

    add_test( NAME ${test}
              COMMAND ${CMAKE_COMMAND} --build . --target ${test_lib} --config $<CONFIGURATION>
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
            )

    set_target_properties ( ${test_lib} PROPERTIES
                            EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            EXCLUDE_FROM_ALL TRUE
                            ${MAKE_UNIT_TARGET_PROPERTIES}
                          )

    target_include_directories( ${test_lib}
                                PRIVATE
                                  ${tts_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/test
                                  ${PROJECT_SOURCE_DIR}/include
                              )

    set_tests_properties( ${test}
                          PROPERTIES WILL_FAIL TRUE
                        )

    add_dependencies(unit ${test})
    add_parent_target(${test})

  endforeach()
endfunction()

##==================================================================================================
## Generate a list of tests from a type list
##==================================================================================================
function (make_units root unit)
  set(sources )

  foreach(e ${ARGN})
    list(APPEND sources "${root}/${e}.cpp")
  endforeach(e)

  make_unit( ${unit} "${sources}" )
endfunction()

##==================================================================================================
## Generate a list of compilation tests from a type list
##==================================================================================================
function (check_failures root unit)
  set(sources )

  foreach(e ${ARGN})
    list(APPEND sources "${root}/${e}.cpp")
  endforeach(e)

  check_failure( ${unit} "${sources}" )
endfunction()

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

##==================================================================================================
## Setup our tests
##==================================================================================================
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.exe              )
add_custom_target(unit.scalar.exe       )
add_custom_target(unit.basic.exe        )
add_custom_target(unit.simd.exe         )
add_custom_target(random.exe            )
add_custom_target(random.scalar.exe     )
add_custom_target(random.simd.exe       )
add_custom_target(exhaustive.exe        )
add_custom_target(exhaustive.scalar.exe )
add_custom_target(exhaustive.simd.exe   )

add_dependencies(unit.exe       doc.exe               )
add_dependencies(unit.exe       unit.scalar.exe       )
add_dependencies(unit.exe       unit.simd.exe         )
add_dependencies(random.exe     random.scalar.exe     )
add_dependencies(random.exe     random.simd.exe       )
add_dependencies(exhaustive.exe exhaustive.scalar.exe )
add_dependencies(exhaustive.exe exhaustive.simd.exe   )

add_dependencies(unit.basic.exe unit.arch.exe   )
add_dependencies(unit.basic.exe unit.api.exe    )
add_dependencies(unit.basic.exe unit.meta.exe   )

##==================================================================================================
## Incldue tests themselves
##==================================================================================================
add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
