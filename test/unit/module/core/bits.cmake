##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Bits-related function unit tests
##==================================================================================================
make_all_units(ROOT core NAME bit_and       ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_andnot    ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_cast      ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_mask      ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_not       ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_notand    ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_notor     ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_or        ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_ornot     ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_select    ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME bit_shl       ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME bit_shr       ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME bit_xor       ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME ceil2         ARCH scalar simd TYPES ${uint_or_real_types}  )
make_all_units(ROOT core NAME firstbitset   ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME firstbitunset ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME floor2        ARCH scalar simd TYPES ${uint_or_real_types}  )
make_all_units(ROOT core NAME is_pow2       ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME popcount      ARCH scalar simd TYPES ${integral_types}      )
make_all_units(ROOT core NAME next          ARCH scalar simd TYPES ${all_types}           )
make_all_units(ROOT core NAME prev          ARCH scalar simd TYPES ${all_types}           )

##==================================================================================================
## Bits-related meta-target
##==================================================================================================
add_custom_target(core.bits.unit)
add_custom_target(core.bits.simd.unit)
add_custom_target(core.bits.scalar.unit)

add_dependencies(core.bits.unit core.bits.simd.unit  )
add_dependencies(core.bits.unit core.bits.scalar.unit)

add_dependencies(core.bits.scalar.unit core.bit_and.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.bit_andnot.regular.scalar.unit    )
add_dependencies(core.bits.scalar.unit core.bit_cast.regular.scalar.unit      )
add_dependencies(core.bits.scalar.unit core.bit_mask.regular.scalar.unit      )
add_dependencies(core.bits.scalar.unit core.bit_not.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.bit_notand.regular.scalar.unit    )
add_dependencies(core.bits.scalar.unit core.bit_notor.regular.scalar.unit     )
add_dependencies(core.bits.scalar.unit core.bit_or.regular.scalar.unit        )
add_dependencies(core.bits.scalar.unit core.bit_ornot.regular.scalar.unit     )
add_dependencies(core.bits.scalar.unit core.bit_select.regular.scalar.unit    )
add_dependencies(core.bits.scalar.unit core.bit_shl.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.bit_shr.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.bit_xor.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.ceil2.regular.scalar.unit         )
add_dependencies(core.bits.scalar.unit core.firstbitset.regular.scalar.unit   )
add_dependencies(core.bits.scalar.unit core.firstbitunset.regular.scalar.unit )
add_dependencies(core.bits.scalar.unit core.floor2.regular.scalar.unit        )
add_dependencies(core.bits.scalar.unit core.is_pow2.regular.scalar.unit       )
add_dependencies(core.bits.scalar.unit core.popcount.regular.scalar.unit      )
add_dependencies(core.bits.scalar.unit core.next.regular.scalar.unit          )
add_dependencies(core.bits.scalar.unit core.next.saturated.scalar.unit        )
add_dependencies(core.bits.scalar.unit core.prev.regular.scalar.unit          )
add_dependencies(core.bits.scalar.unit core.prev.saturated.scalar.unit        )

add_dependencies(core.bits.simd.unit core.bit_and.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.bit_andnot.regular.simd.unit    )
add_dependencies(core.bits.simd.unit core.bit_cast.regular.simd.unit      )
add_dependencies(core.bits.simd.unit core.bit_mask.regular.simd.unit      )
add_dependencies(core.bits.simd.unit core.bit_not.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.bit_notand.regular.simd.unit    )
add_dependencies(core.bits.simd.unit core.bit_notor.regular.simd.unit     )
add_dependencies(core.bits.simd.unit core.bit_or.regular.simd.unit        )
add_dependencies(core.bits.simd.unit core.bit_ornot.regular.simd.unit     )
add_dependencies(core.bits.simd.unit core.bit_select.regular.simd.unit    )
add_dependencies(core.bits.simd.unit core.bit_shl.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.bit_shr.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.bit_xor.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.ceil2.regular.simd.unit         )
add_dependencies(core.bits.simd.unit core.firstbitset.regular.simd.unit   )
add_dependencies(core.bits.simd.unit core.firstbitunset.regular.simd.unit )
add_dependencies(core.bits.simd.unit core.floor2.regular.simd.unit        )
add_dependencies(core.bits.simd.unit core.is_pow2.regular.simd.unit       )
add_dependencies(core.bits.simd.unit core.popcount.regular.simd.unit      )
add_dependencies(core.bits.simd.unit core.next.regular.simd.unit          )
add_dependencies(core.bits.simd.unit core.next.saturated.simd.unit        )
add_dependencies(core.bits.simd.unit core.prev.regular.simd.unit          )
add_dependencies(core.bits.simd.unit core.prev.saturated.simd.unit        )
