##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Wide API tests
make_unit("unit.api.tuple"  wide.cpp                          )
make_unit("unit.api.tuple"  swizzle/broadcast_group.cpp       )
make_unit("unit.api.tuple"  swizzle/broadcast.cpp             )
make_unit("unit.api.tuple"  swizzle/identity.cpp              )
make_unit("unit.api.tuple"  swizzle/reverse.cpp               )
make_unit("unit.api.tuple"  swizzle/slide_left.cpp            )
make_unit("unit.api.tuple"  swizzle/slide_right.cpp           )
make_unit("unit.api.tuple"  swizzle/swap_adjacent_groups.cpp  )
make_unit("unit.api.tuple"  swizzle/zero.cpp                  )
