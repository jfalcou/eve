## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

set(  SOURCES
      ## -------------------------------------------------------------------------------------------
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
