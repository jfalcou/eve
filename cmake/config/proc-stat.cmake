##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## What a translation unit costs to compile, measured on every unit of the build.
##
## -fproc-stat-report makes clang append one line per invocation with the wall time, the user time
## and, above all, the peak memory of that process. Being per process, it is unaffected by -j: the
## figure for a file is the same whether it built alone or alongside fifteen others, where a wall
## clock is not. It writes no JSON and costs nothing measurable, so it can run on every build.
##
## The template-level breakdown is a different tier, see config/time-trace.cmake. That one is heavy
## and stays local.
##======================================================================================================================
option(EVE_PROC_STAT "Record per-translation-unit time and peak memory" OFF)

set( EVE_PROC_STAT_REPORT "${PROJECT_BINARY_DIR}/compile-cost.csv"
     CACHE FILEPATH "CSV receiving one line per compiler invocation"
   )

if( NOT EVE_PROC_STAT )
  return()
endif()

if( NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
  message(WARNING "[eve] EVE_PROC_STAT needs clang, ${CMAKE_CXX_COMPILER_ID} has no -fproc-stat-report")
  return()
endif()

## clang appends, so a stale file from an earlier run would be added to rather than replaced.
file(REMOVE "${EVE_PROC_STAT_REPORT}")

add_compile_options(-fproc-stat-report=${EVE_PROC_STAT_REPORT})

message(STATUS "[eve] Recording compile cost into ${EVE_PROC_STAT_REPORT}")
