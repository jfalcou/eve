##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(  SOURCES
      ## ===========================================================================================
      ## popcnt
      scalar/popcnt/int64.cpp
      scalar/popcnt/int32.cpp
      scalar/popcnt/int16.cpp
      scalar/popcnt/int8.cpp
      scalar/popcnt/uint64.cpp
      scalar/popcnt/uint32.cpp
      scalar/popcnt/uint16.cpp
      scalar/popcnt/uint8.cpp
   )

add_unit_test( "core" ${SOURCES} )
