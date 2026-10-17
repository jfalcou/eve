##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

## The lot of cardinals, see in_lot in test/test.hpp.
set( EVE_TEST_LOT all
     CACHE STRING "Cardinals the unit tests instantiate: all, family, native or extra"
   )
set_property(CACHE EVE_TEST_LOT PROPERTY STRINGS all family native extra)

get_property(lots CACHE EVE_TEST_LOT PROPERTY STRINGS)
if( NOT EVE_TEST_LOT IN_LIST lots )
  message(FATAL_ERROR "EVE_TEST_LOT is '${EVE_TEST_LOT}', expected one of: ${lots}")
endif()

target_compile_definitions(eve_test INTERFACE EVE_TEST_LOT_$<UPPER_CASE:${EVE_TEST_LOT}>)
message(STATUS "[eve] Cardinal lot: ${EVE_TEST_LOT}")

include(${PROJECT_SOURCE_DIR}/cmake/config/aggregated-units.cmake)
