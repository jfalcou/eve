## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

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
