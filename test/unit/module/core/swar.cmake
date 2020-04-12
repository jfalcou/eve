##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## SWAR function unit tests
##==================================================================================================
make_all_units(ROOT core NAME extract   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME lookup    ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME gather    ARCH simd        TYPES ${all_types}     )
#make_all_units(ROOT core NAME shuffle   ARCH scalar simd TYPES ${integral_types})

##==================================================================================================
## SWAR meta-target
##==================================================================================================
add_custom_target(core.swar.unit)
add_custom_target(core.swar.simd.unit)
add_custom_target(core.swar.scalar.unit)

add_dependencies(core.swar.unit core.swar.simd.unit  )
add_dependencies(core.swar.unit core.swar.scalar.unit)

add_dependencies(core.swar.scalar.unit core.extract.regular.scalar.unit )
add_dependencies(core.swar.scalar.unit core.lookup.regular.scalar.unit  )
add_dependencies(core.swar.scalar.unit core.gather.regular.scalar.unit  )

add_dependencies(core.swar.simd.unit core.extract.regular.simd.unit )
add_dependencies(core.swar.simd.unit core.lookup.regular.simd.unit  )
add_dependencies(core.swar.simd.unit core.gather.regular.simd.unit  )
