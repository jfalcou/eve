##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Arithmetic function unit tests
##==================================================================================================
make_all_units(ROOT core NAME abs       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME arg       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME average   ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME cbrt      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME clamp     ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME conj      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME copysign  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME dist      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME fdim      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME fma       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME fms       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME fnma      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME fnms      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME frac      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME hypot     ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME manhattan ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME max       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME maxmag    ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME min       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME minmag    ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME modf      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME negate    ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME negatenz  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME oneminus  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME rec       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME rsqrt     ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME saturate  ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME sign      ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME signnz    ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME sqr       ARCH scalar simd TYPES ${all_types}  )
make_all_units(ROOT core NAME sqr_abs   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT core NAME sqrt      ARCH scalar simd TYPES ${real_types} )

##==================================================================================================
## Arithmetic meta-target
##==================================================================================================
add_custom_target(core.arithmetic.unit)
add_custom_target(core.arithmetic.simd.unit)
add_custom_target(core.arithmetic.scalar.unit)

add_dependencies(core.arithmetic.unit core.arithmetic.simd.unit  )
add_dependencies(core.arithmetic.unit core.arithmetic.scalar.unit)

add_dependencies(core.arithmetic.scalar.unit core.abs.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.abs.saturated.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.arg.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.arg.pedantic.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.average.regular.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.cbrt.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.clamp.regular.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.conj.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.copysign.regular.scalar.unit      )
add_dependencies(core.arithmetic.scalar.unit core.dist.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.dist.saturated.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.fdim.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fma.numeric.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.fma.pedantic.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fma.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.fms.numeric.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.fms.pedantic.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fms.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.fnma.numeric.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fnma.pedantic.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.fnma.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fnms.numeric.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.fnms.pedantic.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.fnms.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.frac.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.hypot.regular.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.manhattan.regular.scalar.unit     )
add_dependencies(core.arithmetic.scalar.unit core.manhattan.pedantic.scalar.unit    )
add_dependencies(core.arithmetic.scalar.unit core.max.numeric.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.max.pedantic.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.max.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.maxmag.numeric.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.maxmag.pedantic.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.maxmag.regular.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.min.numeric.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.min.pedantic.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.min.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.minmag.numeric.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.minmag.pedantic.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.minmag.regular.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.modf.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.negate.regular.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.negatenz.regular.scalar.unit      )
add_dependencies(core.arithmetic.scalar.unit core.negatenz.pedantic.scalar.unit     )
add_dependencies(core.arithmetic.scalar.unit core.oneminus.regular.scalar.unit      )
add_dependencies(core.arithmetic.scalar.unit core.oneminus.regular_if.scalar.unit   )
add_dependencies(core.arithmetic.scalar.unit core.oneminus.saturated.scalar.unit    )
add_dependencies(core.arithmetic.scalar.unit core.oneminus.saturated_if.scalar.unit )
add_dependencies(core.arithmetic.scalar.unit core.rec.raw.scalar.unit               )
add_dependencies(core.arithmetic.scalar.unit core.rec.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.rsqrt.pedantic.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.rsqrt.regular.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.saturate.double.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.saturate.float.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.saturate.int8.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.saturate.int16.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.saturate.int32.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.saturate.int64.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.saturate.uint8.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.saturate.uint16.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.saturate.uint32.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.saturate.uint64.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.sign.regular.scalar.unit          )
add_dependencies(core.arithmetic.scalar.unit core.signnz.regular.scalar.unit        )
add_dependencies(core.arithmetic.scalar.unit core.sqr.regular.scalar.unit           )
add_dependencies(core.arithmetic.scalar.unit core.sqr.saturated.scalar.unit         )
add_dependencies(core.arithmetic.scalar.unit core.sqr_abs.regular.scalar.unit       )
add_dependencies(core.arithmetic.scalar.unit core.sqrt.raw.scalar.unit              )
add_dependencies(core.arithmetic.scalar.unit core.sqrt.regular.scalar.unit          )


add_dependencies(core.arithmetic.simd.unit core.abs.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.abs.saturated.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.arg.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.arg.pedantic.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.average.regular.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.cbrt.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.clamp.regular.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.conj.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.copysign.regular.simd.unit      )
add_dependencies(core.arithmetic.simd.unit core.dist.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.dist.saturated.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.fdim.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fma.numeric.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.fma.pedantic.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fma.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.fms.numeric.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.fms.pedantic.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fms.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.fnma.numeric.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fnma.pedantic.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.fnma.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fnms.numeric.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.fnms.pedantic.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.fnms.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.frac.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.hypot.regular.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.manhattan.regular.simd.unit     )
add_dependencies(core.arithmetic.simd.unit core.manhattan.pedantic.simd.unit    )
add_dependencies(core.arithmetic.simd.unit core.max.numeric.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.max.pedantic.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.max.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.maxmag.numeric.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.maxmag.pedantic.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.maxmag.regular.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.min.numeric.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.min.pedantic.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.min.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.minmag.numeric.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.minmag.pedantic.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.minmag.regular.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.modf.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.negate.regular.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.negatenz.regular.simd.unit      )
add_dependencies(core.arithmetic.simd.unit core.negatenz.pedantic.simd.unit     )
add_dependencies(core.arithmetic.simd.unit core.oneminus.regular.simd.unit      )
add_dependencies(core.arithmetic.simd.unit core.oneminus.regular_if.simd.unit   )
add_dependencies(core.arithmetic.simd.unit core.oneminus.saturated.simd.unit    )
add_dependencies(core.arithmetic.simd.unit core.oneminus.saturated_if.simd.unit )
add_dependencies(core.arithmetic.simd.unit core.rec.raw.simd.unit               )
add_dependencies(core.arithmetic.simd.unit core.rec.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.rsqrt.pedantic.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.rsqrt.regular.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.saturate.double.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.saturate.float.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.saturate.int8.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.saturate.int16.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.saturate.int32.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.saturate.int64.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.saturate.uint8.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.saturate.uint16.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.saturate.uint32.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.saturate.uint64.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.sign.regular.simd.unit          )
add_dependencies(core.arithmetic.simd.unit core.signnz.regular.simd.unit        )
add_dependencies(core.arithmetic.simd.unit core.sqr.regular.simd.unit           )
add_dependencies(core.arithmetic.simd.unit core.sqr.saturated.simd.unit         )
add_dependencies(core.arithmetic.simd.unit core.sqr_abs.regular.simd.unit       )
add_dependencies(core.arithmetic.simd.unit core.sqrt.raw.simd.unit              )
add_dependencies(core.arithmetic.simd.unit core.sqrt.regular.simd.unit          )
