##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(download)
include(generate_test)
include(add_parent_target)

##==================================================================================================
## Common variables
##==================================================================================================
set(_TestCurrentDir "${CMAKE_CURRENT_LIST_DIR}")
set(_TestSrcDir     "${PROJECT_BINARY_DIR}/tmp-src")
if( MSVC )
  set( _TestOptions /std:c++latest -W3 -EHsc)
else()
  set( _TestOptions -std=c++17 -Wall -Wno-missing-braces )
endif()

##==================================================================================================
## Basic type roots
##==================================================================================================
set(real_types      double float                      )
set(int_types       int64 int32 int16 int8            )
set(uint_types      uint64 uint32 uint16 uint8        )
set(integral_types  "${int_types};${uint_types}"      )
set(all_types       "${real_types};${integral_types}" )


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
    generate_test(${root} "" "" ${file})
  endforeach()
endfunction()

##==================================================================================================
## Generate a complete family of test
##==================================================================================================
function(make_all_units)
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

    # Locate relative path for simpler autogen file paths
    file(RELATIVE_PATH base_file ${CMAKE_CURRENT_SOURCE_DIR} ${variant})

    # Generate test for each arch
    foreach( arch ${GEN_TEST_ARCH})
      # Scalar case just uses the types as setup
      if( arch STREQUAL scalar)
        foreach(type ${GEN_TEST_TYPES})
          to_std("${type}" target)
          set(file_to_compile "${_TestSrcDir}/${base_file}.scalar.${type}.cpp")

          configure_file( "${_TestCurrentDir}/scalar.cpp.in" "${file_to_compile}" )
          generate_test ( ${GEN_TEST_ROOT} "${_TestSrcDir}/" "${GEN_TEST_ROOT}.scalar.unit"
                          "${base_file}.scalar.${type}.cpp"
                        )
        endforeach()
      endif()

      # SIMD case uses the types x cardinals as setup
      if( arch STREQUAL simd)
        foreach(type ${GEN_TEST_TYPES})
          to_std("${type}" target)
          set(file_to_compile "${_TestSrcDir}/${base_file}.simd.${type}.cpp")

          configure_file( "${_TestCurrentDir}/simd.cpp.in" "${file_to_compile}" )

          if(GEN_TEST_CARDINAL)
            generate_test ( ${GEN_TEST_ROOT} "${_TestSrcDir}/" "${GEN_TEST_ROOT}.simd.unit"
                            "${base_file}.simd.${type}.cpp"
                            "EVE_CUSTOM_CARDINAL=${GEN_TEST_CARDINAL}"
                          )
          else()
            generate_test ( ${GEN_TEST_ROOT} "${_TestSrcDir}/" "${GEN_TEST_ROOT}.simd.unit"
                            "${base_file}.simd.${type}.cpp"
                          )
          endif()
        endforeach()
      endif()

    endforeach()
  endforeach()
endfunction()

##==================================================================================================
## Create a test that succeed if its compilation fails
##==================================================================================================
function(check_failure root)
  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".unit" base ${file})
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
set(TTS_BUILD_TEST OFF CACHE INTERNAL "OFF")
set(TTS_BUILD_DOC  OFF CACHE INTERNAL "OFF")

download_project( PROJ                tts
                  GIT_REPOSITORY      https://github.com/jfalcou/tts.git
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${tts_SOURCE_DIR} ${tts_BINARY_DIR})

##==================================================================================================
## Setup our tests
##==================================================================================================
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(core.unit)
add_custom_target(core.scalar.unit)
add_custom_target(core.simd.unit)
add_dependencies(core.unit core.scalar.unit)
add_dependencies(core.unit core.simd.unit)

add_custom_target(basic.unit)
add_dependencies(basic.unit arch.unit)
add_dependencies(basic.unit doc.unit)
add_dependencies(basic.unit api.unit)

##==================================================================================================
## Incldue tests themselves
##==================================================================================================
add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
