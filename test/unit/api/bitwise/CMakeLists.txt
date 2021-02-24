##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Bitwise operators

make_all_units(ROOT unit.api  NAME bit_and  ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME bit_or   ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME bit_not  ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME bit_xor  ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME shl      ARCH simd TYPES ${integral_types} )
make_all_units(ROOT unit.api  NAME shr      ARCH simd TYPES ${integral_types} )
