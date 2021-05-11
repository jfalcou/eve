##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
include(target/generate_html)

##==================================================================================================
## Setup a test with many option
##==================================================================================================
function(generate_test root rootpath dep file)
  string(REPLACE ".cpp" ".exe" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})

  if( NOT root STREQUAL "")
    set(test "${root}.${base}")
  else()
    set(test "${base}")
  endif()

  add_executable( ${test}  "${rootpath}${file}")

  if( ${ARGC} EQUAL 5)
    target_compile_definitions( ${test} PUBLIC ${ARGV4})
  endif()

  target_link_libraries(${test} PUBLIC eve_test)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND "${CMAKE_CROSSCOMPILING_CMD}" $<TARGET_FILE:${test}>
            )
  else()
    if ( ${root} MATCHES "doc.*")
      string(REPLACE "." "/" doc_path ${root})
      string(REPLACE ".cpp" ".out.html" doc_output ${file})

      if( EVE_BUILD_SRC_HTML )
        add_test( NAME ${test}
                  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                  COMMAND sh -c "${PROJECT_SOURCE_DIR}/cmake/exe2html.sh $<TARGET_FILE:${test}> \"**Possible output:**\" > ${PROJECT_SOURCE_DIR}/docs/reference/out/${doc_output}"
                )

        generate_html( "test/${doc_path}/${file}" "docs/reference/src" "" "${file}")
      else()

      add_test( NAME ${test}
                  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                  COMMAND "$<TARGET_FILE:${test}>"
                )
      endif()

      if( EVE_USE_PCH )
        target_precompile_headers(${test} REUSE_FROM doc_pch)
        add_dependencies(${test} doc_pch)
      endif()

    else()

      add_test( NAME ${test}
                WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                COMMAND $<TARGET_FILE:${test}>
              )

      if( EVE_USE_PCH )
        target_precompile_headers(${test} REUSE_FROM test_pch)
        add_dependencies(${test} test_pch)
      endif()
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
