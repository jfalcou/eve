##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(  SOURCES
      supports_bmi.cpp
      is_supported.cpp
      current_api.cpp
      expected_cardinal.cpp
      fundamental_cardinal.cpp
      top_bits.cpp
      new_arch_first_tests.cpp
   )

make_unit( "unit.arch" ${SOURCES} )
