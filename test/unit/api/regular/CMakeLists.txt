##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Wide API tests
make_unit("unit.api.regular"  arithmetic.cpp                    )
make_unit("unit.api.regular"  bitwise.cpp                       )
make_unit("unit.api.regular"  comparisons.cpp                   )
make_unit("unit.api.regular"  logicals.cpp                      )
make_unit("unit.api.regular"  shift.cpp                         )
make_unit("unit.api.regular"  wide.cpp                          )
make_unit("unit.api.regular"  swizzle/broadcast_group.cpp       )
make_unit("unit.api.regular"  swizzle/broadcast.cpp             )
make_unit("unit.api.regular"  swizzle/identity.cpp              )
make_unit("unit.api.regular"  swizzle/reverse.cpp               )
make_unit("unit.api.regular"  swizzle/slide_left.cpp            )
make_unit("unit.api.regular"  swizzle/slide_right.cpp           )
make_unit("unit.api.regular"  swizzle/swap_adjacent_groups.cpp  )
make_unit("unit.api.regular"  swizzle/zero.cpp                  )


##==================================================================================================
## Wide related tools
make_unit( "unit.api.regular" conditional.cpp )
make_unit( "unit.api.regular" replace.cpp     )
make_unit( "unit.api.regular" pattern.cpp     )
