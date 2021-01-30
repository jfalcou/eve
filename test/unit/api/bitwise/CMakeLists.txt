##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
