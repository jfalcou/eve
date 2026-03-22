# ##==================================================================================================
# ##  EVE - Expressive Vector Engine
# ##  Copyright : EVE Project Contributors
# ##  SPDX-License-Identifier: BSL-1.0
# ##==================================================================================================

##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup a test with many option
##==================================================================================================
function(generate_bench root rootpath dep file)
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

  if( ${ARGC} EQUAL 5)
    target_compile_definitions( ${test} PUBLIC ${ARGV4})
  endif()

  target_link_libraries(${test} PUBLIC eve_bench)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/benchmarks"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
  add_test( NAME ${test}
            WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/benchmarks"
            COMMAND "${CMAKE_CROSSCOMPILING_CMD}" $<TARGET_FILE:${test}>
          )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/benchmarks"
              COMMAND $<TARGET_FILE:${test}>
            )
  endif()

  if( EVE_USE_PCH )
    target_precompile_headers(${test} REUSE_FROM bench_pch)
    add_dependencies(${test} bench_pch)
  endif()

  set_target_properties ( ${test} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  add_dependencies(bench.exe ${test})

  if( NOT dep STREQUAL "")
    add_dependencies(${dep} ${test})
  endif()

  add_parent_target(${test})
endfunction()

##==================================================================================================
## Setup a basic test
##==================================================================================================
function(make_bench root)
  foreach(file ${ARGN})
    generate_bench(${root} "" "" ${file})
  endforeach()
endfunction()

##==================================================================================================
## Generate tests from a GLOB
##==================================================================================================
function(glob_bench root relative  pattern)
  file(GLOB files CONFIGURE_DEPENDS RELATIVE ${relative} ${pattern})
  foreach(file ${files})
    generate_bench("${root}" "" "" ${file})
  endforeach()
endfunction()
