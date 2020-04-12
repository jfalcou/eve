##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Logical function unit tests
##==================================================================================================
make_all_units(ROOT core NAME binarize        ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME binarize_c      ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME if_else         ARCH scalar simd TYPES ${all_types}     )
##ifnot_else
make_all_units(ROOT core NAME logical_and     ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_andnot  ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_not     ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_notand  ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_notor   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_or      ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_ornot   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME logical_xor     ARCH scalar simd TYPES ${all_types}     )

##==================================================================================================
## Logical meta-target
##==================================================================================================
add_custom_target(core.logical.unit)
add_custom_target(core.logical.simd.unit)
add_custom_target(core.logical.scalar.unit)

add_dependencies(core.logical.unit core.logical.simd.unit  )
add_dependencies(core.logical.unit core.logical.scalar.unit)

add_dependencies(core.logical.scalar.unit core.binarize.regular.scalar.unit       )
add_dependencies(core.logical.scalar.unit core.binarize_c.regular.scalar.unit     )
add_dependencies(core.logical.scalar.unit core.if_else.allbits.scalar.unit        )
add_dependencies(core.logical.scalar.unit core.if_else.mone.scalar.unit           )
add_dependencies(core.logical.scalar.unit core.if_else.one.scalar.unit            )
add_dependencies(core.logical.scalar.unit core.if_else.regular.scalar.unit        )
add_dependencies(core.logical.scalar.unit core.if_else.zero.scalar.unit           )
add_dependencies(core.logical.scalar.unit core.logical_and.regular.scalar.unit    )
add_dependencies(core.logical.scalar.unit core.logical_andnot.regular.scalar.unit )
add_dependencies(core.logical.scalar.unit core.logical_not.regular.scalar.unit    )
add_dependencies(core.logical.scalar.unit core.logical_notand.regular.scalar.unit )
add_dependencies(core.logical.scalar.unit core.logical_notor.regular.scalar.unit  )
add_dependencies(core.logical.scalar.unit core.logical_or.regular.scalar.unit     )
add_dependencies(core.logical.scalar.unit core.logical_ornot.regular.scalar.unit  )
add_dependencies(core.logical.scalar.unit core.logical_xor.regular.scalar.unit    )

add_dependencies(core.logical.simd.unit core.binarize.regular.simd.unit       )
add_dependencies(core.logical.simd.unit core.binarize_c.regular.simd.unit     )
add_dependencies(core.logical.simd.unit core.if_else.allbits.simd.unit        )
add_dependencies(core.logical.simd.unit core.if_else.mone.simd.unit           )
add_dependencies(core.logical.simd.unit core.if_else.one.simd.unit            )
add_dependencies(core.logical.simd.unit core.if_else.regular.simd.unit        )
add_dependencies(core.logical.simd.unit core.if_else.zero.simd.unit           )
add_dependencies(core.logical.simd.unit core.logical_and.regular.simd.unit    )
add_dependencies(core.logical.simd.unit core.logical_andnot.regular.simd.unit )
add_dependencies(core.logical.simd.unit core.logical_not.regular.simd.unit    )
add_dependencies(core.logical.simd.unit core.logical_notand.regular.simd.unit )
add_dependencies(core.logical.simd.unit core.logical_notor.regular.simd.unit  )
add_dependencies(core.logical.simd.unit core.logical_or.regular.simd.unit     )
add_dependencies(core.logical.simd.unit core.logical_ornot.regular.simd.unit  )
add_dependencies(core.logical.simd.unit core.logical_xor.regular.simd.unit    )
