##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Arithmetic operators

make_all_units(ROOT unit.api  NAME plus     ARCH simd TYPES ${all_types}      )
make_all_units(ROOT unit.api  NAME minus    ARCH simd TYPES ${all_types}      )
make_all_units(ROOT unit.api  NAME mul      ARCH simd TYPES ${all_types}      )
make_all_units(ROOT unit.api  NAME div      ARCH simd TYPES ${all_types}      )
make_all_units(ROOT unit.api  NAME modulus  ARCH simd TYPES ${integral_types} )
