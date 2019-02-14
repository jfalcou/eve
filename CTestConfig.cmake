##==================================================================================================
##  TTS - Tiny Test System
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(CTEST_PROJECT_NAME          "EVE")
set(CTEST_NIGHTLY_START_TIME    "01:00:00 UTC")
set(CTEST_DROP_METHOD           "https")
set(CTEST_DROP_SITE             "my.cdash.org")
set(CTEST_DROP_LOCATION         "/submit.php?project=${CTEST_PROJECT_NAME}")
set(CTEST_DROP_SITE_CDASH       TRUE)
set(CTEST_CDASH_VERSION         "2.7")
set(CTEST_CDASH_QUERY_VERSION   TRUE)

# SITE is host name
execute_process(COMMAND hostname OUTPUT_VARIABLE HOST OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "\\.(local|home)$" "" HOST ${HOST})
string(TOLOWER ${HOST} LOWHOST)

set(OS ${CMAKE_SYSTEM_NAME})
string(TOLOWER ${CMAKE_CXX_COMPILER_ID} COMPILER)
string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\1" VERSION_MAJOR "${CMAKE_CXX_COMPILER_VERSION}")
string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\2" VERSION_MINOR "${CMAKE_CXX_COMPILER_VERSION}")

# Compiler version is that of cl.exe, we convert it to MSVC
if(VERSION_MINOR)
  set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
else()
  set(VERSION ${VERSION_MAJOR})
endif()

# We add branch tag if necessary
find_package(Git QUIET)
if(GIT_EXECUTABLE)
  execute_process(COMMAND ${GIT_EXECUTABLE} symbolic-ref HEAD
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE
      RESULT_VARIABLE BRANCH_RESULT ERROR_QUIET
      )
  if(NOT BRANCH_RESULT)
    string(REGEX REPLACE "^.+/([^/]+)$" "\\1" BRANCH ${BRANCH})
  else()
    set(BRANCH "dirty")
  endif()
endif()

set(COMPILER "${COMPILER}-${VERSION}")
set(BUILDNAME "${OS}-${COMPILER}@${BRANCH}")
set(CTEST_BUILD_NAME "${BUILDNAME}")
set(SITE "${LOWHOST}")
set(CTEST_SITE "${SITE}")
