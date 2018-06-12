##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(  SOURCES
      pack/splat/double.cpp
      pack/splat/float.cpp
      pack/splat/int64.cpp
      pack/splat/int32.cpp
      pack/splat/int16.cpp
      pack/splat/int8.cpp
      pack/splat/uint64.cpp
      pack/splat/uint32.cpp
      pack/splat/uint16.cpp
      pack/splat/uint8.cpp
   )

add_unit_test( "api" ${SOURCES} )
