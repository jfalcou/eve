##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Comparisons operators

make_all_units(ROOT unit.api  NAME is_equal         ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME is_not_equal     ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME is_less          ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME is_less_equal    ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME is_greater       ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME is_greater_equal ARCH simd TYPES ${all_types} )
