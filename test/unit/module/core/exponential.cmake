##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Exponential function unit tests
##==================================================================================================
make_all_units(ROOT core NAME exp     ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME exp10   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME exp2    ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME expm1   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME log     ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME log10   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME log1p   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME log2    ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME pow     ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME pow_abs ARCH scalar simd TYPES ${real_types} )

##==================================================================================================
## Exponential meta-target
##==================================================================================================
add_custom_target(core.exponential.unit)
add_custom_target(core.exponential.simd.unit)
add_custom_target(core.exponential.scalar.unit)

add_dependencies(core.exponential.unit core.exponential.simd.unit   )
add_dependencies(core.exponential.unit core.exponential.scalar.unit )

add_dependencies(core.exponential.scalar.unit core.tofloat.regular.scalar.unit  )

add_dependencies(core.exponential.simd.unit core.tofloat.regular.simd.unit      )

add_dependencies(core.exponential.scalar.unit core.exp.pedantic.scalar.unit     )
add_dependencies(core.exponential.scalar.unit core.exp.regular.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.exp10.pedantic.scalar.unit   )
add_dependencies(core.exponential.scalar.unit core.exp10.regular.scalar.unit    )
add_dependencies(core.exponential.scalar.unit core.exp2.pedantic.scalar.unit    )
add_dependencies(core.exponential.scalar.unit core.exp2.regular.scalar.unit     )
add_dependencies(core.exponential.scalar.unit core.expm1.regular.scalar.unit    )
add_dependencies(core.exponential.scalar.unit core.log.musl.scalar.unit         )
add_dependencies(core.exponential.scalar.unit core.log.plain.scalar.unit        )
add_dependencies(core.exponential.scalar.unit core.log.regular.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.log10.musl.scalar.unit       )
add_dependencies(core.exponential.scalar.unit core.log10.plain.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.log10.regular.scalar.unit    )
add_dependencies(core.exponential.scalar.unit core.log1p.musl.scalar.unit       )
add_dependencies(core.exponential.scalar.unit core.log1p.plain.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.log1p.regular.scalar.unit    )
add_dependencies(core.exponential.scalar.unit core.log2.musl.scalar.unit        )
add_dependencies(core.exponential.scalar.unit core.log2.plain.scalar.unit       )
add_dependencies(core.exponential.scalar.unit core.log2.regular.scalar.unit     )
add_dependencies(core.exponential.scalar.unit core.pow.raw.scalar.unit          )
add_dependencies(core.exponential.scalar.unit core.pow.regular.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.pow_abs.raw.scalar.unit      )
add_dependencies(core.exponential.scalar.unit core.pow_abs.regular.scalar.unit  )

add_dependencies(core.exponential.simd.unit core.exp.pedantic.simd.unit     )
add_dependencies(core.exponential.simd.unit core.exp.regular.simd.unit      )
add_dependencies(core.exponential.simd.unit core.exp10.pedantic.simd.unit   )
add_dependencies(core.exponential.simd.unit core.exp10.regular.simd.unit    )
add_dependencies(core.exponential.simd.unit core.exp2.pedantic.simd.unit    )
add_dependencies(core.exponential.simd.unit core.exp2.regular.simd.unit     )
add_dependencies(core.exponential.simd.unit core.expm1.regular.simd.unit    )
add_dependencies(core.exponential.simd.unit core.log.musl.simd.unit         )
add_dependencies(core.exponential.simd.unit core.log.plain.simd.unit        )
add_dependencies(core.exponential.simd.unit core.log.regular.simd.unit      )
add_dependencies(core.exponential.simd.unit core.log10.musl.simd.unit       )
add_dependencies(core.exponential.simd.unit core.log10.plain.simd.unit      )
add_dependencies(core.exponential.simd.unit core.log10.regular.simd.unit    )
add_dependencies(core.exponential.simd.unit core.log1p.musl.simd.unit       )
add_dependencies(core.exponential.simd.unit core.log1p.plain.simd.unit      )
add_dependencies(core.exponential.simd.unit core.log1p.regular.simd.unit    )
add_dependencies(core.exponential.simd.unit core.log2.musl.simd.unit        )
add_dependencies(core.exponential.simd.unit core.log2.plain.simd.unit       )
add_dependencies(core.exponential.simd.unit core.log2.regular.simd.unit     )
add_dependencies(core.exponential.simd.unit core.pow.raw.simd.unit          )
add_dependencies(core.exponential.simd.unit core.pow.regular.simd.unit      )
add_dependencies(core.exponential.simd.unit core.pow_abs.raw.simd.unit      )
add_dependencies(core.exponential.simd.unit core.pow_abs.regular.simd.unit  )
