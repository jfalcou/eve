##======================================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## How many of the heaviest units may compile at once.
##
## A build's appetite is set by its unluckiest draw: at -j 10 with nothing holding them back, ten of
## the heaviest units can land together and ask for 31 GiB. A Ninja pool bounds that set, and the
## bound is what lets two agents share a host without the reaper arbitrating between them.
##
## The depth belongs to the machine, not to the repository: it is a cache variable each job sets.
## Zero leaves every target where it was, which is what a generator other than Ninja gets anyway.
##
## The list of targets comes from the measurement, see config/heavy-units.cmake.
##======================================================================================================================
set( EVE_HEAVY_POOL 0
     CACHE STRING "How many targets from heavy-units.cmake may compile at once, 0 to not pool them"
   )

include(${PROJECT_SOURCE_DIR}/cmake/config/heavy-units.cmake)

if( EVE_HEAVY_POOL GREATER 0 )
  set_property(GLOBAL APPEND PROPERTY JOB_POOLS heavy=${EVE_HEAVY_POOL})
  list(LENGTH EVE_HEAVY_TARGETS eve_heavy_count)
  message(STATUS "[eve] ${eve_heavy_count} heavy targets compile ${EVE_HEAVY_POOL} at a time")
endif()
