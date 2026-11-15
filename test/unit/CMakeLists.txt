##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(unit_root "${PROJECT_SOURCE_DIR}/test/unit")
set(module_root "${PROJECT_SOURCE_DIR}/test/unit/module")

##==================================================================================================
## GLOB and process arch unit tests
##==================================================================================================
add_custom_target(unit.api.exe         )
add_dependencies(unit.exe unit.api.exe )
glob_unit("unit" ${unit_root} "api/*.cpp" RECURSE AGGREGATED)

##==================================================================================================
## GLOB and process arch unit tests
##==================================================================================================
add_custom_target(unit.arch.exe         )
add_dependencies(unit.exe unit.arch.exe )
glob_unit("unit" ${unit_root} "arch/*.cpp")

##==================================================================================================
## GLOB and process config unit tests
##==================================================================================================
add_custom_target(unit.config.exe         )
add_dependencies(unit.exe unit.config.exe )
glob_unit("unit" ${unit_root} "config/*.cpp")

##==================================================================================================
## Checks of the source tree, written in Python under tools/
##==================================================================================================
find_package(Python3 COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
  add_test( NAME unit.internals.include_rules
            COMMAND ${Python3_EXECUTABLE} -B ${PROJECT_SOURCE_DIR}/tools/include_rules/check.py ${PROJECT_SOURCE_DIR}
          )
  add_test( NAME unit.internals.include_rules.unittest
            COMMAND ${Python3_EXECUTABLE} -B -m unittest test_check
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools/include_rules
          )
else()
  message(WARNING "[eve] Python 3 not found: the source tree checks under tools/ are not run")
endif()

add_test( NAME unit.arch.namespace_macros.cmake
          COMMAND ${CMAKE_COMMAND} -DEVE_INCLUDE=${PROJECT_SOURCE_DIR}/include
                  -P ${unit_root}/arch/namespace_macros.cmake
        )

## Calls code compiled for the current platform from a translation unit compiled without SIMD,
## passing ABI independent types between them.
set(abi_independent_link unit.arch.abi_independent_link.exe)
add_executable( ${abi_independent_link}
                ${unit_root}/arch/abi_independent/scalar.cpp
                ${unit_root}/arch/abi_independent/native.cpp
              )
set_source_files_properties ( ${unit_root}/arch/abi_independent/scalar.cpp
                              PROPERTIES COMPILE_DEFINITIONS EVE_NO_SIMD
                            )
target_link_libraries(${abi_independent_link} PUBLIC eve_test)
set_target_properties ( ${abi_independent_link} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE
                        EXCLUDE_FROM_ALL TRUE
                      )
add_test( NAME ${abi_independent_link}
          WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
          COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${abi_independent_link}>
        )
add_dependencies(unit ${abi_independent_link})
add_parent_target(${abi_independent_link})

##==================================================================================================
## GLOB and process internals unit tests
##==================================================================================================
add_custom_target(unit.internals.exe         )
add_dependencies(unit.exe unit.internals.exe )
glob_unit("unit" ${unit_root} "internals/*.cpp")

##==================================================================================================
## GLOB and process memory unit tests
##==================================================================================================
add_custom_target(unit.memory.exe         )
add_dependencies(unit.exe unit.memory.exe )
glob_unit("unit" ${unit_root} "memory/*.cpp" RECURSE AGGREGATED)

##==================================================================================================
## GLOB and process meta unit tests
##==================================================================================================
add_custom_target(unit.meta.exe         )
add_dependencies(unit.exe unit.meta.exe )
glob_unit("unit" ${unit_root} "meta/*.cpp"         )
glob_unit("unit" ${unit_root} "meta/concepts/*.cpp")
glob_unit("unit" ${unit_root} "meta/traits/*.cpp"  )

##==================================================================================================
## GLOB and process meta unit tests
##==================================================================================================
add_custom_target(unit.regression.exe         )
add_dependencies(unit.exe unit.regression.exe )
glob_unit("unit" ${unit_root} "regression/*.cpp" )

##==================================================================================================
## GLOB and process modules unit tests
##==================================================================================================
add_custom_target(unit.algo.exe         )
add_dependencies(unit.exe unit.algo.exe )
glob_unit("unit" ${unit_root} "module/algo/*.cpp"          )
glob_unit("unit" ${unit_root} "module/algo/algorithm/*.cpp")
glob_unit("unit" ${unit_root} "module/algo/container/*.cpp")
glob_unit("unit" ${unit_root} "module/algo/views/*.cpp"    )

add_custom_target(unit.core.exe         )
add_dependencies(unit.exe unit.core.exe )
glob_unit("unit" ${unit_root} "module/core/*.cpp"          )
glob_unit("unit" ${unit_root} "module/core/constant/*.cpp"  )
glob_unit("unit" ${unit_root} "module/core/convert/*.cpp"   AGGREGATED)
glob_unit("unit" ${unit_root} "module/core/saturate/*.cpp" )

add_custom_target(unit.combinatorial.exe         )
add_dependencies(unit.exe unit.combinatorial.exe )
glob_unit("unit" ${unit_root} "module/combinatorial/*.cpp" )

add_custom_target(unit.bessel.exe         )
add_dependencies(unit.exe unit.bessel.exe )
glob_unit("unit" ${unit_root} "module/bessel/*.cpp" )

add_custom_target(unit.elliptic.exe         )
add_dependencies(unit.exe unit.elliptic.exe )
glob_unit("unit" ${unit_root} "module/elliptic/*.cpp" )

add_custom_target(unit.math.exe         )
add_dependencies(unit.exe unit.math.exe )
glob_unit("unit" ${unit_root} "module/math/*.cpp" )
glob_unit("unit" ${unit_root} "module/math/constant/*.cpp" )

add_custom_target(unit.polynomial.exe         )
add_dependencies(unit.exe unit.polynomial.exe )
glob_unit("unit" ${unit_root} "module/polynomial/*.cpp" )

add_custom_target(unit.special.exe         )
add_dependencies(unit.exe unit.special.exe )
glob_unit("unit" ${unit_root} "module/special/*.cpp" )
