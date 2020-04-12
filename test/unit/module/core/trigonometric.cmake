##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Trigonometric function unit tests
##==================================================================================================
make_all_units(ROOT core NAME cos         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME cospi       ARCH scalar simd TYPES ${signed_types}  )
make_all_units(ROOT core NAME cot         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME cotpi       ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME csc         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME cscpi       ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME sec         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME secpi       ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME sin         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME sincos      ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME sinpi       ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME sinpicospi  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME tan         ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME tanpi       ARCH scalar simd TYPES ${real_types}    )
#quadrant

##==================================================================================================
## Trigonometric meta-target
##==================================================================================================
add_custom_target(core.trigonometric.unit)
add_custom_target(core.trigonometric.simd.unit)
add_custom_target(core.trigonometric.scalar.unit)

add_dependencies(core.trigonometric.unit core.trigonometric.simd.unit  )
add_dependencies(core.trigonometric.unit core.trigonometric.scalar.unit)

add_dependencies(core.trigonometric.scalar.unit core.cos.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cos.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cos.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cos.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cos.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cospi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cospi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cospi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cospi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cot.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cot.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cot.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cot.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cot.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cotpi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cotpi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cotpi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cotpi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.csc.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.csc.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.csc.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.csc.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.csc.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cscpi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cscpi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cscpi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.cscpi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sec.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sec.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sec.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sec.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sec.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.secpi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.secpi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.secpi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.secpi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sin.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sin.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sin.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sin.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sin.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sincos.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sincos.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sincos.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sincos.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sincos.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpicospi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpicospi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpicospi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.sinpicospi.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tan.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tan.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tan.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tan.restricted.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tan.small.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tanpi.big.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tanpi.medium.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tanpi.regular.scalar.unit  )
add_dependencies(core.trigonometric.scalar.unit core.tanpi.restricted.scalar.unit  )

add_dependencies(core.trigonometric.simd.unit core.cos.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cos.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cos.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cos.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cos.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cospi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cospi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cospi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cospi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cot.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cot.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cot.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cot.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cot.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cotpi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cotpi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cotpi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cotpi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.csc.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.csc.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.csc.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.csc.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.csc.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cscpi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cscpi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cscpi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.cscpi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sec.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sec.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sec.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sec.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sec.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.secpi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.secpi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.secpi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.secpi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sin.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sin.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sin.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sin.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sin.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sincos.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sincos.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sincos.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sincos.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sincos.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpicospi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpicospi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpicospi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.sinpicospi.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tan.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tan.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tan.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tan.restricted.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tan.small.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tanpi.big.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tanpi.medium.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tanpi.regular.simd.unit  )
add_dependencies(core.trigonometric.simd.unit core.tanpi.restricted.simd.unit  )
