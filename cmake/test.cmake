## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

## Centralize all required setup for unit tests
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
                  PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test"
                )

    set_target_properties ( ${test} PROPERTIES
                            EXCLUDE_FROM_DEFAULT_BUILD TRUE
                            EXCLUDE_FROM_ALL TRUE
                            ${MAKE_UNIT_TARGET_PROPERTIES}
                          )

    add_dependencies(unit ${test})

    add_test( NAME ${test} COMMAND ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/test"
            )
  endforeach()
endfunction()

include(download)

## Disable testing LEST
set(LEST_BUILD_TEST OFF CACHE INTERNAL    "OFF")
set(LEST_BUILD_EXAMPLE OFF CACHE INTERNAL "OFF")

download_project( PROJ                lest
                  GIT_REPOSITORY      https://github.com/martinmoene/lest
                  GIT_TAG             master
                  "UPDATE_DISCONNECTED 1"
                  QUIET
                )

add_subdirectory(${lest_SOURCE_DIR} ${lest_BINARY_DIR})
include_directories("${lest_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")

## Setup our tests
add_custom_target(tests)
add_custom_target(unit)
add_dependencies(tests unit)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
