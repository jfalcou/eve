##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup a test with many option
##==================================================================================================
function(generate_test root rootpath dep file)
  ## AGGREGATED gives the test twice the native cardinal.
  cmake_parse_arguments(GT "AGGREGATED" "" "" ${ARGN})
  string(REPLACE ".cpp"    ".exe" base ${file})
  string(REPLACE "/"       "."    base ${base})
  string(REPLACE "\\"      "."    base ${base})
  string(REPLACE "module." ""     base ${base})

  if( NOT root STREQUAL "")
    set(test "${root}.${base}")
  else()
    set(test "${base}")
  endif()

  add_executable( ${test}  "${rootpath}${file}")

  ## A target the measurement found heavy waits for a slot rather than piling onto the others.
  if( EVE_HEAVY_POOL GREATER 0 AND ${test} IN_LIST EVE_HEAVY_TARGETS )
    set_target_properties(${test} PROPERTIES JOB_POOL_COMPILE heavy)
  endif()

  set(pch test_pch)
  if( GT_AGGREGATED OR ${test} IN_LIST EVE_AGGREGATED_TARGETS )
    target_compile_definitions( ${test} PRIVATE EVE_TEST_WITH_AGGREGATED)
    set(pch test_pch_aggregated)
  endif()

  target_link_libraries(${test} PUBLIC eve_test)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if ( (${root} MATCHES "doc.*") OR (${root} MATCHES "examples.*") )
    if (CMAKE_CROSSCOMPILING_CMD)
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND "${CMAKE_CROSSCOMPILING_CMD}" $<TARGET_FILE:${test}>
              )
    else()
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND $<TARGET_FILE:${test}>
              )
    endif()

    if( EVE_USE_PCH )
      target_precompile_headers(${test} REUSE_FROM doc_pch)
      add_dependencies(${test} doc_pch)
    endif()

  else()
    if (CMAKE_CROSSCOMPILING_CMD)
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND "${CMAKE_CROSSCOMPILING_CMD}" $<TARGET_FILE:${test}>
              )
    else()
      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND $<TARGET_FILE:${test}>
              )
    endif()

    if( EVE_USE_PCH )
      target_precompile_headers(${test} REUSE_FROM ${pch})
      add_dependencies(${test} ${pch})
    endif()
  endif()

  set_target_properties ( ${test} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  add_dependencies(unit ${test})

  if( NOT dep STREQUAL "")
    add_dependencies(${dep} ${test})
  endif()

  add_parent_target(${test})
endfunction()

##==================================================================================================
## Setup a basic test
##==================================================================================================
function(make_unit root)
  foreach(file ${ARGN})
    generate_test(${root} "" "" ${file})
  endforeach()
endfunction()

##==================================================================================================
## Generate tests from a GLOB
##==================================================================================================
function(glob_unit root relative  pattern)
  ## RECURSE globs the subdirectories too, and AGGREGATED gives every test twice the native
  ## cardinal.
  cmake_parse_arguments(GU "RECURSE;AGGREGATED" "" "" ${ARGN})
  if( GU_RECURSE )
    file(GLOB_RECURSE files CONFIGURE_DEPENDS RELATIVE ${relative} ${pattern})
  else()
    file(GLOB files CONFIGURE_DEPENDS RELATIVE ${relative} ${pattern})
  endif()
  set(aggregated "")
  if( GU_AGGREGATED )
    set(aggregated AGGREGATED)
  endif()
  foreach(file ${files})
    generate_test("${root}" "" "" ${file} ${aggregated})
  endforeach()
endfunction()
