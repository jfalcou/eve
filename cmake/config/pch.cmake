##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup PCH
##==================================================================================================
add_executable(bench_pch  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/benchmarks/bench_pch.cpp> )
add_executable(test_pch   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/test_pch.cpp>)
add_executable(doc_pch    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/doc_pch.cpp> )

target_link_libraries(bench_pch PUBLIC eve_bench)
target_link_libraries(test_pch  PUBLIC eve_test)
target_link_libraries(doc_pch   PUBLIC eve_test)

set_property( TARGET bench_pch  PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bench" )
set_property( TARGET test_pch   PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )
set_property( TARGET doc_pch    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit" )

set_target_properties ( bench_pch PROPERTIES
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE
                        EXCLUDE_FROM_ALL TRUE
                        ${MAKE_UNIT_TARGET_PROPERTIES}
                      )

set_target_properties ( test_pch PROPERTIES
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE
                        EXCLUDE_FROM_ALL TRUE
                        ${MAKE_UNIT_TARGET_PROPERTIES}
                      )

set_target_properties ( doc_pch PROPERTIES
                        EXCLUDE_FROM_DEFAULT_BUILD TRUE
                        EXCLUDE_FROM_ALL TRUE
                        ${MAKE_UNIT_TARGET_PROPERTIES}
                      )

target_precompile_headers(bench_pch PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/benchmarks/generators.hpp>)
target_precompile_headers(bench_pch PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/benchmarks/experiment.hpp>)
target_precompile_headers(bench_pch PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eve/wide.hpp>)
target_precompile_headers(test_pch  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/test/test.hpp>)
target_precompile_headers(doc_pch   PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eve/wide.hpp>)
