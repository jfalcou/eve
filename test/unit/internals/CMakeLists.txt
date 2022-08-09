##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.internals.exe )

##==================================================================================================
## List internal tests
##==================================================================================================
make_unit( "unit.internals" aggregation.cpp                     )
make_unit( "unit.internals" byte_16_runtime_shuffle.cpp         )
make_unit( "unit.internals" compress/compress_mask_num.cpp      )
make_unit( "unit.internals" dispatch.cpp                        )
make_unit( "unit.internals" horn.cpp                            )
make_unit( "unit.internals" horn1.cpp                           )
make_unit( "unit.internals" meta.cpp                            )
make_unit( "unit.internals" optimize_pattern.cpp                )
make_unit( "unit.internals" to_logical.cpp                      )
