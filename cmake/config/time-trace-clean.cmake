##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================
## Removes the traces left by an earlier build, and the objects that go with them. Run through
## `cmake -P` because the cleanup has to happen before the build, and `cmake -E rm` expands no
## wildcard.
##
## The objects go too: a trace is written as a side effect of compiling, so dropping the JSON alone
## leaves the build up to date, nothing recompiles and no trace comes back. A measurement recompiles
## what it measures.
##======================================================================================================================
file(GLOB_RECURSE eve_stale "${EVE_TIME_TRACE_SCAN}/*.json"
                            "${EVE_TIME_TRACE_SCAN}/*.o"
                            "${EVE_TIME_TRACE_SCAN}/*.obj"
    )
list(LENGTH eve_stale eve_stale_count)

if( eve_stale_count )
  file(REMOVE ${eve_stale})
  message(STATUS "[eve] Removed ${eve_stale_count} stale trace(s) and object(s)")
endif()
