##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## General meta tests
make_unit( "meta" as_floating_point.cpp )
make_unit( "meta" as_integer.cpp )
make_unit( "meta" as_wide.cpp )
make_unit( "meta" sign_of.cpp )

##==================================================================================================
## Traits tests
make_unit( "meta" has_abi.cpp )
make_unit( "meta" element_type.cpp )
