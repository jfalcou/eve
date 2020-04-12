##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Predicates function unit tests
##==================================================================================================
make_all_units(ROOT core NAME is_denormal     ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_even         ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_finite       ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_flint        ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_imag         ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME is_infinite     ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_nan          ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_negative     ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_normal       ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_not_denormal ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_not_finite   ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_not_imag     ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME is_not_inf      ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_not_nan      ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_not_real     ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME is_odd          ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_ordered      ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_positive     ARCH scalar simd TYPES ${all_types}   )
make_all_units(ROOT core NAME is_real         ARCH scalar simd TYPES ${real_types}  )
make_all_units(ROOT core NAME is_unordered    ARCH scalar simd TYPES ${all_types}   )

##==================================================================================================
## Predicates meta-target
##==================================================================================================
add_custom_target(core.predicates.unit)
add_custom_target(core.predicates.simd.unit)
add_custom_target(core.predicates.scalar.unit)

add_dependencies(core.predicates.unit core.predicates.simd.unit  )
add_dependencies(core.predicates.unit core.predicates.scalar.unit)

add_dependencies(core.predicates.scalar.unit core.is_denormal.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_even.regular.scalar.unit         )
add_dependencies(core.predicates.scalar.unit core.is_finite.regular.scalar.unit       )
add_dependencies(core.predicates.scalar.unit core.is_flint.regular.scalar.unit        )
add_dependencies(core.predicates.scalar.unit core.is_imag.regular.scalar.unit         )
add_dependencies(core.predicates.scalar.unit core.is_infinite.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_nan.regular.scalar.unit          )
add_dependencies(core.predicates.scalar.unit core.is_negative.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_normal.regular.scalar.unit       )
add_dependencies(core.predicates.scalar.unit core.is_not_denormal.regular.scalar.unit )
add_dependencies(core.predicates.scalar.unit core.is_not_finite.regular.scalar.unit   )
add_dependencies(core.predicates.scalar.unit core.is_not_imag.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_not_inf.regular.scalar.unit      )
add_dependencies(core.predicates.scalar.unit core.is_not_nan.regular.scalar.unit      )
add_dependencies(core.predicates.scalar.unit core.is_not_real.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_odd.regular.scalar.unit          )
add_dependencies(core.predicates.scalar.unit core.is_ordered.regular.scalar.unit      )
add_dependencies(core.predicates.scalar.unit core.is_positive.regular.scalar.unit     )
add_dependencies(core.predicates.scalar.unit core.is_real.regular.scalar.unit         )
add_dependencies(core.predicates.scalar.unit core.is_unordered.regular.scalar.unit    )

add_dependencies(core.predicates.simd.unit core.is_denormal.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_even.regular.simd.unit         )
add_dependencies(core.predicates.simd.unit core.is_finite.regular.simd.unit       )
add_dependencies(core.predicates.simd.unit core.is_flint.regular.simd.unit        )
add_dependencies(core.predicates.simd.unit core.is_imag.regular.simd.unit         )
add_dependencies(core.predicates.simd.unit core.is_infinite.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_nan.regular.simd.unit          )
add_dependencies(core.predicates.simd.unit core.is_negative.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_normal.regular.simd.unit       )
add_dependencies(core.predicates.simd.unit core.is_not_denormal.regular.simd.unit )
add_dependencies(core.predicates.simd.unit core.is_not_finite.regular.simd.unit   )
add_dependencies(core.predicates.simd.unit core.is_not_imag.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_not_inf.regular.simd.unit      )
add_dependencies(core.predicates.simd.unit core.is_not_nan.regular.simd.unit      )
add_dependencies(core.predicates.simd.unit core.is_not_real.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_odd.regular.simd.unit          )
add_dependencies(core.predicates.simd.unit core.is_ordered.regular.simd.unit      )
add_dependencies(core.predicates.simd.unit core.is_positive.regular.simd.unit     )
add_dependencies(core.predicates.simd.unit core.is_real.regular.simd.unit         )
add_dependencies(core.predicates.simd.unit core.is_unordered.regular.simd.unit    )
