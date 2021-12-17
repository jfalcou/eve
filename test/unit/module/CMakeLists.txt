##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_subdirectory(real)

## NEw Modules
add_subdirectory(polynomial)

if(EVE_USE_BOOST)
add_subdirectory(bessel)
add_subdirectory(combinatorial)
add_subdirectory(special)
endif()