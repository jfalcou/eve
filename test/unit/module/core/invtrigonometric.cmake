##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Inverse trigonometric function unit tests
##==================================================================================================
make_all_units(ROOT core NAME acos    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acosd   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acospi  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acot    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acotd   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acotpi  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acscd   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acsc    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME acscpi  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asec    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asecd   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asecpi  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asin    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asind   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME asinpi  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atan    ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atan2   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atan2d  ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atan2pi ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atand   ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME atanpi  ARCH scalar simd TYPES ${real_types}  )

##==================================================================================================
## Inverse trigonometric meta-target
##==================================================================================================
add_custom_target(core.invtrigonometric.unit)
add_custom_target(core.invtrigonometric.simd.unit)
add_custom_target(core.invtrigonometric.scalar.unit)

add_dependencies(core.invtrigonometric.unit core.invtrigonometric.simd.unit  )
add_dependencies(core.invtrigonometric.unit core.invtrigonometric.scalar.unit)

add_dependencies(core.invtrigonometric.scalar.unit core.acos.raw.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acos.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acosd.raw.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acosd.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acospi.pedantic.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acospi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acot.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acotd.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acotpi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acscd.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acsc.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.acscpi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asec.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asecd.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asecpi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asin.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asind.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.asinpi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2d.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2pi.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2.pedantic.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2d.pedantic.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atan2pi.pedantic.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atand.regular.scalar.unit  )
add_dependencies(core.invtrigonometric.scalar.unit core.atanpi.regular.scalar.unit  )

add_dependencies(core.invtrigonometric.simd.unit core.acos.raw.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acos.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acosd.raw.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acosd.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acospi.pedantic.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acospi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acot.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acotd.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acotpi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acscd.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acsc.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.acscpi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asec.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asecd.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asecpi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asin.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asind.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.asinpi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2d.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2pi.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2.pedantic.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2d.pedantic.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atan2pi.pedantic.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atand.regular.simd.unit  )
add_dependencies(core.invtrigonometric.simd.unit core.atanpi.regular.simd.unit  )
