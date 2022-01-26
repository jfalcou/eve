##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
set(  SOURCES
      supports_bmi.cpp
      is_supported.cpp
      current_api.cpp
      expected_cardinal.cpp
      fundamental_cardinal.cpp
   )

make_unit( "unit.arch" ${SOURCES} )
