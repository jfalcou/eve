##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Wide API tests over User Defined Type
make_unit("unit.api.udt"  conditional.cpp  )
make_unit("unit.api.udt"  comparison.cpp   )
make_unit("unit.api.udt"  product_type.cpp )
make_unit("unit.api.udt"  wide.cpp         )
make_unit("unit.api.udt"  zip.cpp          )
