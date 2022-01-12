##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.core.exe                )
add_custom_target(unit.real.core.constant.exe       )
add_custom_target(unit.real.core.constant.scalar.exe)
add_custom_target(unit.real.core.constant.simd.exe  )
add_custom_target(unit.real.core.scalar.exe         )
add_custom_target(unit.real.core.simd.exe           )

add_dependencies(unit.real.scalar.exe        unit.real.core.scalar.exe          )
add_dependencies(unit.real.simd.exe          unit.real.core.simd.exe            )
add_dependencies(unit.real.core.constant.exe unit.real.core.constant.scalar.exe )
add_dependencies(unit.real.core.constant.exe unit.real.core.constant.simd.exe   )
add_dependencies(unit.real.core.scalar.exe   unit.real.core.constant.scalar.exe )
add_dependencies(unit.real.core.simd.exe     unit.real.core.constant.simd.exe   )
add_dependencies(unit.real.core.exe          unit.real.core.constant.exe        )
add_dependencies(unit.real.core.exe          unit.real.core.scalar.exe          )
add_dependencies(unit.real.core.exe          unit.real.core.simd.exe            )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.core"  bit_and.cpp              )
make_unit("unit.real.core"  bit_andnot.cpp           )
make_unit("unit.real.core"  bit_cast.cpp             )
make_unit("unit.real.core"  bit_ceil.cpp             )
make_unit("unit.real.core"  bit_floor.cpp            )
make_unit("unit.real.core"  bit_mask.cpp             )
make_unit("unit.real.core"  bit_not.cpp              )
make_unit("unit.real.core"  bit_notand.cpp           )
make_unit("unit.real.core"  bit_or.cpp               )
make_unit("unit.real.core"  bit_ornot.cpp            )
make_unit("unit.real.core"  bit_notor.cpp            )
make_unit("unit.real.core"  bit_select.cpp           )
make_unit("unit.real.core"  bit_shl.cpp              )
make_unit("unit.real.core"  bit_shr.cpp              )
make_unit("unit.real.core"  bit_width.cpp            )
make_unit("unit.real.core"  bit_xor.cpp              )
make_unit("unit.real.core"  bitofsign.cpp            )
make_unit("unit.real.core"  countl_one.cpp           )
make_unit("unit.real.core"  countl_zero.cpp          )
make_unit("unit.real.core"  countr_one.cpp           )
make_unit("unit.real.core"  countr_zero.cpp          )
make_unit("unit.real.core"  epsilon.cpp              )
make_unit("unit.real.core"  firstbitset.cpp          )
make_unit("unit.real.core"  firstbitunset.cpp        )
make_unit("unit.real.core"  fdim.cpp                 )
make_unit("unit.real.core"  has_single_bit.cpp       )
make_unit("unit.real.core"  if_else.cpp              )
make_unit("unit.real.core"  is_pow2.cpp              )
make_unit("unit.real.core"  lookup.cpp               )
make_unit("unit.real.core"  logical_and.cpp          )
make_unit("unit.real.core"  logical_andnot.cpp       )
make_unit("unit.real.core"  logical_not.cpp          )
make_unit("unit.real.core"  logical_notand.cpp       )
make_unit("unit.real.core"  logical_notor.cpp        )
make_unit("unit.real.core"  logical_or.cpp           )
make_unit("unit.real.core"  logical_ornot.cpp        )
make_unit("unit.real.core"  logical_xor.cpp          )
make_unit("unit.real.core"  lohi.cpp                 )
make_unit("unit.real.core"  modf.cpp                 )

make_unit("unit.real.core"  convert/to_double.cpp    )
make_unit("unit.real.core"  convert/to_float.cpp     )
make_unit("unit.real.core"  convert/to_int64.cpp     )
make_unit("unit.real.core"  convert/to_int32.cpp     )
make_unit("unit.real.core"  convert/to_int16.cpp     )
make_unit("unit.real.core"  convert/to_int8.cpp      )
make_unit("unit.real.core"  convert/to_uint64.cpp    )
make_unit("unit.real.core"  convert/to_uint32.cpp    )
make_unit("unit.real.core"  convert/to_uint16.cpp    )
make_unit("unit.real.core"  convert/to_uint8.cpp     )
make_unit("unit.real.core"  convert/to_tuple.cpp     )

##==================================================================================================
## Other tests
##==================================================================================================
add_subdirectory(failure)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT unit.real.core NAME gather                ARCH        simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME iceil                 ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME ifloor                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME inearest              ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME iround                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME itrunc                ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.core NAME saturate              ARCH scalar simd TYPES ${all_types}     )
