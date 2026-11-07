##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Removes the counters of a previous run, by 'cmake -DEVE_COVERAGE_BUILD=<dir> -P coverage-clean.cmake'.
## gcov stops on a counter file whose object file a rebuild replaced.
##======================================================================================================================
file(GLOB_RECURSE eve_stale_counters "${EVE_COVERAGE_BUILD}/*.gcda")

if( eve_stale_counters )
  file(REMOVE ${eve_stale_counters})
endif()
