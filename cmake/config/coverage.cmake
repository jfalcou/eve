##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Coverage of include/eve by the unit tests, with the flags, the tools, and the targets of copa_setup_coverage.
##
## eve-coverage runs the tests under instrumentation, and eve-coverage-report writes coverage/index.html and the
## coverage/summary.json that the coverage workflow of copacabana turns into the job summary.
##======================================================================================================================
option(EVE_ENABLE_COVERAGE "Build the unit tests with coverage instrumentation and enable the coverage targets" OFF)

if( NOT EVE_ENABLE_COVERAGE )
  return()
endif()

if( NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" )
  message(FATAL_ERROR "[eve] EVE_ENABLE_COVERAGE needs g++ or clang++, got ${CMAKE_CXX_COMPILER_ID}")
endif()

find_program(EVE_GCOVR gcovr)

if( NOT EVE_GCOVR )
  message(FATAL_ERROR "[eve] EVE_ENABLE_COVERAGE needs gcovr, install it with 'pip install gcovr==7.*'")
endif()

## gcovr 8 sums the lines of a header once per unit that includes it, so its totals exceed the files.
execute_process(COMMAND ${EVE_GCOVR} --version OUTPUT_VARIABLE eve_gcovr_version OUTPUT_STRIP_TRAILING_WHITESPACE)

if( eve_gcovr_version MATCHES "gcovr ([0-9]+)" AND CMAKE_MATCH_1 GREATER_EQUAL 8 )
  message(WARNING "[eve] gcovr ${CMAKE_MATCH_1} inflates the totals of a header, the CI reads them with gcovr 7")
endif()

## A gcov reads the notes of its own major version only, and gcovr reports any other as an unknown working directory.
string(REGEX MATCH "^[0-9]+" eve_compiler_major "${CMAKE_CXX_COMPILER_VERSION}")

if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  ## Distributions ship llvm-cov under its versioned name, often without the plain one.
  find_program(EVE_LLVM_COV NAMES "llvm-cov-${eve_compiler_major}" llvm-cov)

  if( NOT EVE_LLVM_COV )
    message(FATAL_ERROR "[eve] EVE_ENABLE_COVERAGE with clang needs llvm-cov, "
                        "install package llvm-${eve_compiler_major}")
  endif()

  execute_process(COMMAND ${EVE_LLVM_COV} --version OUTPUT_VARIABLE eve_cov_version OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX MATCH "LLVM version ([0-9]+)" eve_cov_match "${eve_cov_version}")

  set(eve_cov_major       "${CMAKE_MATCH_1}")
  set(eve_cov_name        "llvm-cov")
  set(eve_cov_package     "llvm-${eve_compiler_major}")
  set(eve_gcov_tool       "${EVE_LLVM_COV} gcov")
  set(eve_coverage_flags  --coverage)
else()
  find_program(EVE_GCOV NAMES "gcov-${eve_compiler_major}" gcov)

  if( NOT EVE_GCOV )
    message(FATAL_ERROR "[eve] EVE_ENABLE_COVERAGE with g++ needs gcov-${eve_compiler_major}")
  endif()

  execute_process(COMMAND ${EVE_GCOV} --version OUTPUT_VARIABLE eve_cov_version OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX MATCH "gcov \\([^)]*\\) ([0-9]+)" eve_cov_match "${eve_cov_version}")

  set(eve_cov_major       "${CMAKE_MATCH_1}")
  set(eve_cov_name        "gcov")
  set(eve_cov_package     "gcc-${eve_compiler_major}")
  set(eve_gcov_tool       "${EVE_GCOV}")

  ## Without -fprofile-abs-path, the notes name a header relative to the object file and gcov finds none of eve.
  set(eve_coverage_flags  --coverage -fprofile-abs-path)
endif()

if( NOT eve_cov_major STREQUAL eve_compiler_major )
  message(FATAL_ERROR "[eve] ${eve_cov_name} ${eve_cov_major} cannot read the notes of "
                      "${CMAKE_CXX_COMPILER_ID} ${eve_compiler_major}, install package ${eve_cov_package}")
endif()

## Do not drop -fprofile-update=atomic: the threads of inclusive_scan_par_unseq race on the counters,
## and gcovr stops on the negative hits gcov then reports.
target_compile_options(eve_test INTERFACE ${eve_coverage_flags} -fprofile-update=atomic)
target_link_options(eve_test INTERFACE --coverage)

set(eve_coverage_dir "${PROJECT_BINARY_DIR}/coverage")

## The search stays on this build tree: from --root alone, gcovr enters a sibling tree built by another compiler,
## whose notes this gcov refuses. deps/ holds kumi, raberu, and spy, which their own repositories measure.
set( eve_gcovr_command
     ${EVE_GCOVR} "${PROJECT_BINARY_DIR}" --root "${PROJECT_SOURCE_DIR}"
     --filter "${PROJECT_SOURCE_DIR}/include/eve/" --exclude "${PROJECT_SOURCE_DIR}/include/eve/deps/"
     --gcov-executable "${eve_gcov_tool}" --exclude-unreachable-branches --exclude-throw-branches --print-summary
   )

add_custom_target( eve-coverage-report
                   COMMAND ${CMAKE_COMMAND} -E make_directory "${eve_coverage_dir}"
                   COMMAND ${eve_gcovr_command} --html-details "${eve_coverage_dir}/index.html"
                           --json-summary "${eve_coverage_dir}/summary.json" --json-summary-pretty
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
                   COMMENT "[eve] Writing the coverage report in ${eve_coverage_dir}"
                   VERBATIM
                 )

## unit.exe builds the unit tests and the examples, not the doc tests, and ctest fails a test without its executable.
add_custom_target( eve-coverage
                   COMMAND ${CMAKE_COMMAND} -DEVE_COVERAGE_BUILD=${PROJECT_BINARY_DIR}
                                            -P "${PROJECT_SOURCE_DIR}/cmake/config/coverage-clean.cmake"
                   COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --no-tests=error --timeout 3600
                                                  --exclude-regex "^doc\\."
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
                   COMMENT "[eve] Running the unit tests under coverage"
                   VERBATIM
                 )

add_dependencies(eve-coverage-report eve-coverage)
add_dependencies(eve-coverage unit.exe)

message(STATUS "[eve] Coverage with ${eve_cov_name}, eve-coverage-report writes ${eve_coverage_dir}")
