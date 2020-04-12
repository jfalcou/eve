##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Conversion function unit tests
##==================================================================================================
make_all_units(ROOT core NAME convert               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME tofloat               ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME toint                 ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME touint                ARCH scalar simd TYPES ${all_types}     )

##==================================================================================================
## Conversion meta-target
##==================================================================================================
add_custom_target(core.conversion.unit)
add_custom_target(core.conversion.simd.unit)
add_custom_target(core.conversion.scalar.unit)

add_dependencies(core.conversion.unit core.conversion.simd.unit   )
add_dependencies(core.conversion.unit core.conversion.scalar.unit )

add_dependencies(core.conversion.scalar.unit core.tofloat.regular.scalar.unit           )
add_dependencies(core.conversion.scalar.unit core.toint.regular.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.touint.regular.scalar.unit            )
add_dependencies(core.conversion.scalar.unit core.convert.double.scalar.unit            )
add_dependencies(core.conversion.scalar.unit core.convert.double_saturated.scalar.unit  )
add_dependencies(core.conversion.scalar.unit core.convert.float.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.convert.float_saturated.scalar.unit   )
add_dependencies(core.conversion.scalar.unit core.convert.int16.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.convert.int16_saturated.scalar.unit   )
add_dependencies(core.conversion.scalar.unit core.convert.int32.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.convert.int32_saturated.scalar.unit   )
add_dependencies(core.conversion.scalar.unit core.convert.int64.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.convert.int64_saturated.scalar.unit   )
add_dependencies(core.conversion.scalar.unit core.convert.int8.scalar.unit              )
add_dependencies(core.conversion.scalar.unit core.convert.int8_saturated.scalar.unit    )
add_dependencies(core.conversion.scalar.unit core.convert.uint16.scalar.unit            )
add_dependencies(core.conversion.scalar.unit core.convert.uint16_saturated.scalar.unit  )
add_dependencies(core.conversion.scalar.unit core.convert.uint32.scalar.unit            )
add_dependencies(core.conversion.scalar.unit core.convert.uint32_saturated.scalar.unit  )
add_dependencies(core.conversion.scalar.unit core.convert.uint64.scalar.unit            )
add_dependencies(core.conversion.scalar.unit core.convert.uint64_saturated.scalar.unit  )
add_dependencies(core.conversion.scalar.unit core.convert.uint8.scalar.unit             )
add_dependencies(core.conversion.scalar.unit core.convert.uint8_saturated.scalar.unit   )

add_dependencies(core.conversion.simd.unit core.tofloat.regular.simd.unit           )
add_dependencies(core.conversion.simd.unit core.toint.regular.simd.unit             )
add_dependencies(core.conversion.simd.unit core.touint.regular.simd.unit            )
add_dependencies(core.conversion.simd.unit core.convert.double.simd.unit            )
add_dependencies(core.conversion.simd.unit core.convert.double_saturated.simd.unit  )
add_dependencies(core.conversion.simd.unit core.convert.float.simd.unit             )
add_dependencies(core.conversion.simd.unit core.convert.float_saturated.simd.unit   )
add_dependencies(core.conversion.simd.unit core.convert.int16.simd.unit             )
add_dependencies(core.conversion.simd.unit core.convert.int16_saturated.simd.unit   )
add_dependencies(core.conversion.simd.unit core.convert.int32.simd.unit             )
add_dependencies(core.conversion.simd.unit core.convert.int32_saturated.simd.unit   )
add_dependencies(core.conversion.simd.unit core.convert.int64.simd.unit             )
add_dependencies(core.conversion.simd.unit core.convert.int64_saturated.simd.unit   )
add_dependencies(core.conversion.simd.unit core.convert.int8.simd.unit              )
add_dependencies(core.conversion.simd.unit core.convert.int8_saturated.simd.unit    )
add_dependencies(core.conversion.simd.unit core.convert.uint16.simd.unit            )
add_dependencies(core.conversion.simd.unit core.convert.uint16_saturated.simd.unit  )
add_dependencies(core.conversion.simd.unit core.convert.uint32.simd.unit            )
add_dependencies(core.conversion.simd.unit core.convert.uint32_saturated.simd.unit  )
add_dependencies(core.conversion.simd.unit core.convert.uint64.simd.unit            )
add_dependencies(core.conversion.simd.unit core.convert.uint64_saturated.simd.unit  )
add_dependencies(core.conversion.simd.unit core.convert.uint8.simd.unit             )
add_dependencies(core.conversion.simd.unit core.convert.uint8_saturated.simd.unit   )
