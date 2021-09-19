##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.internals.exe )
add_dependencies(unit.simd.exe unit.internals.exe )

##==================================================================================================
## List internal tests
##==================================================================================================
make_unit( "unit.internals" aggregation.cpp                     )
make_unit( "unit.internals" compress_store_swizzle_mask_num.cpp )
make_unit( "unit.internals" dispatch.cpp                        )
make_unit( "unit.internals" meta.cpp                            )
make_unit( "unit.internals" optimize_pattern.cpp                )
make_unit( "unit.internals" to_logical.cpp                      )
make_unit( "unit.internals" top_bits.cpp                        )
