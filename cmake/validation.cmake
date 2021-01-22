##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##===================================================================================================
## Build a validation test
##===================================================================================================
function(build_test root)

  set(test "validation.${root}.exe")
  add_executable(${test} ${ARGN})
  add_dependencies(validation ${test})

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/validation"
              )

  target_link_libraries(${test} PUBLIC eve_test)

  target_include_directories( ${test}
                              PUBLIC
                                $<INSTALL_INTERFACE:include>
                                $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                              PRIVATE
                                ${tts_SOURCE_DIR}/include
                                ${PROJECT_SOURCE_DIR}/test
                            )

  add_test( NAME ${test}
            WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/${location}"
            COMMAND $<TARGET_FILE:${test}>
          )

  add_parent_target(${test})
  add_dependencies(${test} test_pch)

  target_precompile_headers(${test} REUSE_FROM test_pch)

endfunction()

##==================================================================================================
## Setup aggregation of validation targets
##==================================================================================================
add_custom_target(validation)
add_custom_target(validation.exe        )
add_custom_target(validation.scalar.exe )
add_custom_target(validation.basic.exe  )
add_custom_target(validation.simd.exe   )

add_dependencies(validation.exe       validation.scalar.exe )
add_dependencies(validation.exe       validation.simd.exe   )
add_dependencies(validation.basic.exe validation.arch.exe   )
# add_dependencies(validation.basic.exe validation.api.exe    )
# add_dependencies(validation.basic.exe validation.meta.exe   )
