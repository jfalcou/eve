##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup a test with many option
##==================================================================================================
function(generate_test root rootpath dep file)
  string(REPLACE ".cpp" ".unit" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "${root}.${base}")

  add_executable( ${test}  "${rootpath}${file}")

  if( ${ARGC} EQUAL 5)
    target_compile_definitions( ${test} PUBLIC ${ARGV4})
  endif()

  target_compile_options  ( ${test} PUBLIC ${_TestOptions} )

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

  if( NOT dep STREQUAL "")
    add_dependencies(${dep} ${test})
  endif()

  add_parent_target(${test})
endfunction()
