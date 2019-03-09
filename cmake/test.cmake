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
## Basic type roots
##==================================================================================================
set(real_types      double float                      )
set(int_types       int64 int32 int16 int8            )
set(uint_types      uint64 uint32 uint16 uint8        )
set(integral_types  "${int_types};${uint_types}"      )
set(all_types       "${real_types};${integral_types}" )

##==================================================================================================
## Centralize all required setup for unit tests
##==================================================================================================
function(add_unit_test root)
  if( MSVC )
    set( options /std:c++latest -W3 -EHsc)
  else()
    set( options -std=c++17 -Wall -Wno-missing-braces )
  endif()

  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".unit" base ${file})
    string(REPLACE "/"    "." base ${base})
    string(REPLACE "\\"   "." base ${base})
    set(test "${root}.${base}")

    add_executable( ${test}  ${file})
    target_compile_options  ( ${test} PUBLIC ${options} )

    set_property( TARGET ${test}
                  PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                )

    if (CMAKE_CROSSCOMPILING_CMD)
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}> --no-color --pass
              )
    else()
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND $<TARGET_FILE:${test}> --no-color --pass
              )
    endif()

    set_target_properties ( ${test} PROPERTIES
                            EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            EXCLUDE_FROM_ALL TRUE
                            ${MAKE_UNIT_TARGET_PROPERTIES}
                          )

    target_include_directories( ${test}
                                PRIVATE
                                  ${tts_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/test
                                  ${PROJECT_SOURCE_DIR}/include
                              )

    target_link_libraries(${test} tts)
    add_dependencies(unit ${test})

    add_parent_target(${test})
  endforeach()
endfunction()

##==================================================================================================
## Create a test that succeed if its compilation fails
##==================================================================================================
function(add_build_test root)
  if( MSVC )
    set( options /std:c++latest -W3 -EHsc)
  else()
    set( options -std=c++17 -Wall -Wno-missing-braces )
  endif()

  foreach(file ${ARGN})
    string(REPLACE ".cpp" ".unit" base ${file})
    string(REPLACE "/"    "." base ${base})
    string(REPLACE "\\"   "." base ${base})
    set(test "${root}.${base}")

    set( test_lib "${test}_lib")
    add_library( ${test_lib} OBJECT EXCLUDE_FROM_ALL ${file})
    target_compile_options  ( ${test_lib} PUBLIC ${options} )

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
function (list_tests root unit)
  set(sources )

  foreach(e ${ARGN})
    list(APPEND sources "${root}/${e}.cpp")
  endforeach(e)

  add_unit_test( ${unit} "${sources}" )
endfunction()

##==================================================================================================
## Generate a list of compilation tests from a type list
##==================================================================================================
function (list_build_tests root unit)
  set(sources )

  foreach(e ${ARGN})
    list(APPEND sources "${root}/${e}.cpp")
  endforeach(e)

  add_build_test( ${unit} "${sources}" )
endfunction()

##==================================================================================================
## Disable testing/doc for tts
set(TTS_BUILD_TEST OFF CACHE INTERNAL "OFF")
set(TTS_BUILD_DOC  OFF CACHE INTERNAL "OFF")

download_project( PROJ                tts
                  GIT_REPOSITORY      https://github.com/jfalcou/tts.git
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${tts_SOURCE_DIR} ${tts_BINARY_DIR})

## Setup our tests
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
