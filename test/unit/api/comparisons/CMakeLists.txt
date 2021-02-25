##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
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
