##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.api.exe       )
add_custom_target(unit.api.scalar.exe)
add_custom_target(unit.api.simd.exe  )

add_dependencies(unit.scalar.exe    unit.api.scalar.exe )
add_dependencies(unit.simd.exe      unit.api.simd.exe   )
add_dependencies(unit.api.exe       unit.api.scalar.exe )
add_dependencies(unit.api.exe       unit.api.simd.exe   )

##==================================================================================================
## Wide API tests
make_unit("unit.api"  arithmetic.cpp                    )
make_unit("unit.api"  bitwise.cpp                       )
make_unit("unit.api"  comparisons.cpp                   )
make_unit("unit.api"  logicals.cpp                      )
make_unit("unit.api"  shift.cpp                         )
make_unit("unit.api"  wide.cpp                          )
make_unit("unit.api"  swizzle/broadcast_group.cpp       )
make_unit("unit.api"  swizzle/broadcast.cpp             )
make_unit("unit.api"  swizzle/identity.cpp              )
make_unit("unit.api"  swizzle/reverse.cpp               )
make_unit("unit.api"  swizzle/slide_left.cpp            )
make_unit("unit.api"  swizzle/swap_adjacent_groups.cpp  )
make_unit("unit.api"  swizzle/zero.cpp                  )


##==================================================================================================
## Wide related tools
make_unit( "unit.api" conditional.cpp )
make_unit( "unit.api" replace.cpp     )
make_unit( "unit.api" pattern.cpp     )
