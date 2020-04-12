##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Reduction function unit tests
##==================================================================================================
make_all_units(ROOT core NAME all     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME any     ARCH scalar simd TYPES ${all_types} )
#sum
#prod
#maximum
#minimum
make_all_units(ROOT core NAME nbtrue  ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME none  ARCH scalar simd TYPES ${all_types}   )

##==================================================================================================
## Reduction meta-target
##==================================================================================================
add_custom_target(core.reduction.unit)
add_custom_target(core.reduction.simd.unit)
add_custom_target(core.reduction.scalar.unit)

add_dependencies(core.reduction.unit core.reduction.simd.unit  )
add_dependencies(core.reduction.unit core.reduction.scalar.unit)

add_dependencies(core.reduction.scalar.unit core.all.regular.scalar.unit    )
add_dependencies(core.reduction.scalar.unit core.any.regular.scalar.unit    )
add_dependencies(core.reduction.scalar.unit core.nbtrue.regular.scalar.unit )
add_dependencies(core.reduction.scalar.unit core.none.regular.scalar.unit   )

add_dependencies(core.reduction.simd.unit core.all.regular.simd.unit    )
add_dependencies(core.reduction.simd.unit core.any.regular.simd.unit    )
add_dependencies(core.reduction.simd.unit core.nbtrue.regular.simd.unit )
add_dependencies(core.reduction.simd.unit core.none.regular.simd.unit   )
