##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Comparisons function unit tests
##==================================================================================================
make_all_units(ROOT core NAME is_equal              ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_eqz                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_gez                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_greater            ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_greater_equal      ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_gtz                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_less               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_less_equal         ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_lessgreater        ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_lez                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_ltz                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_nez                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_ngez               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_ngtz               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_nlez               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_nltz               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_not_equal          ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_not_greater        ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_not_greater_equal  ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_not_less           ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME is_not_less_equal     ARCH scalar simd TYPES ${all_types}     )

##==================================================================================================
## Comparisons meta-target
##==================================================================================================
add_custom_target(core.comparison.unit)
add_custom_target(core.comparison.simd.unit)
add_custom_target(core.comparison.scalar.unit)

add_dependencies(core.comparison.unit core.comparison.simd.unit  )
add_dependencies(core.comparison.unit core.comparison.scalar.unit)

add_dependencies(core.comparison.scalar.unit core.is_equal.regular.scalar.unit              )
add_dependencies(core.comparison.scalar.unit core.is_equal.numeric.scalar.unit              )
add_dependencies(core.comparison.scalar.unit core.is_eqz.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_gez.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_greater.regular.scalar.unit            )
add_dependencies(core.comparison.scalar.unit core.is_greater_equal.regular.scalar.unit      )
add_dependencies(core.comparison.scalar.unit core.is_gtz.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_less.regular.scalar.unit               )
add_dependencies(core.comparison.scalar.unit core.is_less_equal.regular.scalar.unit         )
add_dependencies(core.comparison.scalar.unit core.is_lessgreater.regular.scalar.unit        )
add_dependencies(core.comparison.scalar.unit core.is_lez.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_ltz.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_nez.regular.scalar.unit                )
add_dependencies(core.comparison.scalar.unit core.is_ngez.regular.scalar.unit               )
add_dependencies(core.comparison.scalar.unit core.is_ngtz.regular.scalar.unit               )
add_dependencies(core.comparison.scalar.unit core.is_nlez.regular.scalar.unit               )
add_dependencies(core.comparison.scalar.unit core.is_nltz.regular.scalar.unit               )
add_dependencies(core.comparison.scalar.unit core.is_not_equal.regular.scalar.unit          )
add_dependencies(core.comparison.scalar.unit core.is_not_equal.numeric.scalar.unit          )
add_dependencies(core.comparison.scalar.unit core.is_not_greater.regular.scalar.unit        )
add_dependencies(core.comparison.scalar.unit core.is_not_greater_equal.regular.scalar.unit  )
add_dependencies(core.comparison.scalar.unit core.is_not_less.regular.scalar.unit           )
add_dependencies(core.comparison.scalar.unit core.is_not_less_equal.regular.scalar.unit     )

add_dependencies(core.comparison.simd.unit core.is_equal.regular.simd.unit              )
add_dependencies(core.comparison.simd.unit core.is_equal.numeric.simd.unit              )
add_dependencies(core.comparison.simd.unit core.is_eqz.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_gez.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_greater.regular.simd.unit            )
add_dependencies(core.comparison.simd.unit core.is_greater_equal.regular.simd.unit      )
add_dependencies(core.comparison.simd.unit core.is_gtz.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_less.regular.simd.unit               )
add_dependencies(core.comparison.simd.unit core.is_less_equal.regular.simd.unit         )
add_dependencies(core.comparison.simd.unit core.is_lessgreater.regular.simd.unit        )
add_dependencies(core.comparison.simd.unit core.is_lez.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_ltz.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_nez.regular.simd.unit                )
add_dependencies(core.comparison.simd.unit core.is_ngez.regular.simd.unit               )
add_dependencies(core.comparison.simd.unit core.is_ngtz.regular.simd.unit               )
add_dependencies(core.comparison.simd.unit core.is_nlez.regular.simd.unit               )
add_dependencies(core.comparison.simd.unit core.is_nltz.regular.simd.unit               )
add_dependencies(core.comparison.simd.unit core.is_not_equal.regular.simd.unit          )
add_dependencies(core.comparison.simd.unit core.is_not_equal.numeric.simd.unit          )
add_dependencies(core.comparison.simd.unit core.is_not_greater.regular.simd.unit        )
add_dependencies(core.comparison.simd.unit core.is_not_greater_equal.regular.simd.unit  )
add_dependencies(core.comparison.simd.unit core.is_not_less.regular.simd.unit           )
add_dependencies(core.comparison.simd.unit core.is_not_less_equal.regular.simd.unit     )
