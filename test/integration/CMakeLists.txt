##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0-1.0
##==================================================================================================

# Extract HEAD from git
find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE eve_git_head
    RESULT_VARIABLE _git_error
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT _git_error STREQUAL "0")
    message(SEND_ERROR
        "Failed to extract EVE's current git commit for integration tests: ${_git_error}")
    return()
endif()


# Builds and tests a separate project as an EVE test
function(eve_build_and_ctest project_name)
  string(REPLACE "-test" "" test_name "integration.${project_name}.exe")

  add_test(
    NAME ${test_name}
    COMMAND
    "${CMAKE_CTEST_COMMAND}"
    --verbose
    --output-on-failure
    --build-generator "${CMAKE_GENERATOR}"
    --build-and-test
      "${CMAKE_CURRENT_SOURCE_DIR}/${project_name}"
      "${CMAKE_CURRENT_BINARY_DIR}/${project_name}"
    --build-options ${ARGN}
    --test-command "${CMAKE_CTEST_COMMAND}")
endfunction()


##==================================================================================================
## Create Integration Tests
##==================================================================================================

## ===== CPM =====
eve_build_and_ctest(cpm-test
    "-Deve_git_head=${eve_git_head}"
    "-Deve_SOURCE_DIR=${eve_SOURCE_DIR}"
    # cpm-test internally sets EVE_* configure options
)

## ===== Fetch =====
eve_build_and_ctest(fetch-test
    "-Deve_git_head=${eve_git_head}"
    "-Deve_SOURCE_DIR=${eve_SOURCE_DIR}"
    "-DEVE_BUILD_TEST=OFF"
    "-DEVE_BUILD_DOCUMENTATION=OFF"
)

## ===== Install =====
# install eve as its own test and for 'install-test' to find
set(eve_ROOT "${PROJECT_BINARY_DIR}/test/integration/install")
add_test(
  NAME integration.install-eve.exe
  COMMAND
  "${CMAKE_COMMAND}"
  --install "${PROJECT_BINARY_DIR}"
  --verbose
  --prefix  "${eve_ROOT}")

eve_build_and_ctest(install-test "-Deve_ROOT=${eve_ROOT}")
set_tests_properties(integration.install.exe PROPERTIES DEPENDS integration.install-eve.exe)

## ==== Aggregated ====
add_custom_target(integration
  COMMAND
  "${CMAKE_CTEST_COMMAND}"
  --test-dir "${PROJECT_BINARY_DIR}"
  --output-on-failure
  -R integration\.[a-z-]+\.exe)
