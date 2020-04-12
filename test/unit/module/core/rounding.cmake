##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Rounding function unit tests
##==================================================================================================
make_all_units(ROOT core NAME ceil      ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME floor     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME iceil     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME ifloor    ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME inearest  ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME iround    ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME itrunc    ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME nearest   ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME round     ARCH scalar simd TYPES ${all_types} )
make_all_units(ROOT core NAME trunc     ARCH scalar simd TYPES ${all_types} )

##==================================================================================================
## Rounding meta-target
##==================================================================================================
add_custom_target(core.rounding.unit)
add_custom_target(core.rounding.simd.unit)
add_custom_target(core.rounding.scalar.unit)

add_dependencies(core.rounding.unit core.rounding.simd.unit  )
add_dependencies(core.rounding.unit core.rounding.scalar.unit)

add_dependencies(core.rounding.scalar.unit core.ceil.regular.scalar.unit      )
add_dependencies(core.rounding.scalar.unit core.floor.regular.scalar.unit     )
add_dependencies(core.rounding.scalar.unit core.iceil.regular.scalar.unit     )
add_dependencies(core.rounding.scalar.unit core.ifloor.regular.scalar.unit    )
add_dependencies(core.rounding.scalar.unit core.inearest.regular.scalar.unit  )
add_dependencies(core.rounding.scalar.unit core.iround.regular.scalar.unit    )
add_dependencies(core.rounding.scalar.unit core.itrunc.regular.scalar.unit    )
add_dependencies(core.rounding.scalar.unit core.nearest.regular.scalar.unit   )
add_dependencies(core.rounding.scalar.unit core.round.regular.scalar.unit     )
add_dependencies(core.rounding.scalar.unit core.trunc.regular.scalar.unit     )

add_dependencies(core.rounding.simd.unit core.ceil.regular.simd.unit      )
add_dependencies(core.rounding.simd.unit core.floor.regular.simd.unit     )
add_dependencies(core.rounding.simd.unit core.iceil.regular.simd.unit     )
add_dependencies(core.rounding.simd.unit core.ifloor.regular.simd.unit    )
add_dependencies(core.rounding.simd.unit core.inearest.regular.simd.unit  )
add_dependencies(core.rounding.simd.unit core.iround.regular.simd.unit    )
add_dependencies(core.rounding.simd.unit core.itrunc.regular.simd.unit    )
add_dependencies(core.rounding.simd.unit core.nearest.regular.simd.unit   )
add_dependencies(core.rounding.simd.unit core.round.regular.simd.unit     )
add_dependencies(core.rounding.simd.unit core.trunc.regular.simd.unit     )
