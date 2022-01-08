##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_subdirectory(real)

## New Modules
add_subdirectory(arithmetic)
add_subdirectory(ieee)
add_subdirectory(polynomial)
add_subdirectory(proba)

if(EVE_USE_BOOST)
add_subdirectory(bessel)
add_subdirectory(elliptic)
add_subdirectory(combinatorial)
add_subdirectory(math)
add_subdirectory(special)
endif()