##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Where the compile cost of a translation unit comes from.
##
## -ftime-trace makes clang write one JSON per TU with a per-phase and per-template-instantiation
## breakdown, and ClangBuildAnalyzer turns a tree of those into a ranking of the costliest files,
## templates and functions. That ranking only means something over a large corpus, so the target
## aggregates whatever was built rather than one file at a time.
##
## This is deliberately not part of a normal build: -ftime-trace slows compilation down and writes
## about a megabyte per TU. Peak memory is measured elsewhere, by -fproc-stat-report, which is cheap
## enough to run on every pull request.
##======================================================================================================================
option(EVE_TIME_TRACE "Emit -ftime-trace and enable the time-trace target" OFF)

set( EVE_TIME_TRACE_TARGET "unit.exe"
     CACHE STRING "What the time-trace target builds before aggregating"
   )

set( EVE_TIME_TRACE_REPORT "${PROJECT_BINARY_DIR}/time-trace"
     CACHE PATH "Directory receiving the capture and the report"
   )

if( NOT EVE_TIME_TRACE )
  return()
endif()

if( NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  message(WARNING "[eve] EVE_TIME_TRACE needs clang, ${CMAKE_CXX_COMPILER_ID} has no -ftime-trace")
  return()
endif()

##======================================================================================================================
## ClangBuildAnalyzer comes from the system when it is there, and is built from source otherwise.
## FetchContent rather than CPM: it ships with CMake, where CPM would mean vendoring a file into a
## project that has no dependency infrastructure at all today.
##
## TODO: drop the FetchContent block when EVE moves to copacabana. CPM comes with it, and the whole
## else() branch below becomes CPMAddPackage("gh:aras-p/ClangBuildAnalyzer@1.6.0").
##
## It has to be brought in *before* -ftime-trace is added, or it would be compiled with it and drop
## its own traces next to EVE's, in the very tree the analysis walks.
##======================================================================================================================
find_program(EVE_CLANG_BUILD_ANALYZER NAMES ClangBuildAnalyzer)

if( EVE_CLANG_BUILD_ANALYZER )
  set(eve_cba_command "${EVE_CLANG_BUILD_ANALYZER}")
  message(STATUS "[eve] Using ClangBuildAnalyzer from ${EVE_CLANG_BUILD_ANALYZER}")
else()
  include(FetchContent)
  FetchContent_Declare( ClangBuildAnalyzer
                        GIT_REPOSITORY https://github.com/aras-p/ClangBuildAnalyzer.git
                        GIT_TAG        v1.6.0
                        GIT_SHALLOW    TRUE
                      )
  FetchContent_MakeAvailable(ClangBuildAnalyzer)
  set(eve_cba_command "$<TARGET_FILE:ClangBuildAnalyzer>")
  message(STATUS "[eve] ClangBuildAnalyzer built from source, v1.6.0")
endif()

add_compile_options(-ftime-trace)

##======================================================================================================================
## The target builds ${EVE_TIME_TRACE_TARGET} itself, between the cleanup and the aggregation.
##
## The cleanup cannot be a separate target: nothing orders a custom target before the build of
## another one, and aggregating a tree where half the traces are left from an earlier build yields
## an average of two states with nothing saying so. Building from inside makes that impossible.
##======================================================================================================================
## The scan is rooted on the test tree rather than on the whole build directory: FetchContent drops
## ClangBuildAnalyzer's own sources under _deps, and those ship thirty-odd JSON fixtures that CBA
## would happily aggregate as if they were ours.
set( EVE_TIME_TRACE_SCAN "${PROJECT_BINARY_DIR}/test"
     CACHE PATH "Tree the traces are collected from"
   )

add_custom_target( time-trace
                   COMMAND ${CMAKE_COMMAND} -DEVE_TIME_TRACE_SCAN=${EVE_TIME_TRACE_SCAN}
                                            -P "${PROJECT_SOURCE_DIR}/cmake/config/time-trace-clean.cmake"
                   COMMAND ${CMAKE_COMMAND} -E make_directory "${EVE_TIME_TRACE_REPORT}"
                   COMMAND ${CMAKE_COMMAND} --build "${PROJECT_BINARY_DIR}"
                                            --target ${EVE_TIME_TRACE_TARGET}
                   COMMAND ${eve_cba_command} --all "${EVE_TIME_TRACE_SCAN}"
                                                       "${EVE_TIME_TRACE_REPORT}/capture.bin"
                   COMMAND ${eve_cba_command} --analyze
                                                       "${EVE_TIME_TRACE_REPORT}/capture.bin"
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
                   COMMENT "[eve] Building ${EVE_TIME_TRACE_TARGET} with -ftime-trace, then analyzing"
                   USES_TERMINAL VERBATIM
                 )

message(STATUS "[eve] time-trace target builds ${EVE_TIME_TRACE_TARGET}, report in ${EVE_TIME_TRACE_REPORT}")
