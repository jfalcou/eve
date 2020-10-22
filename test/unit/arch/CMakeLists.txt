##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

set(  SOURCES
      is_supported.cpp
      expected_cardinal.cpp
   )

make_unit( "unit.arch" ${SOURCES} )
