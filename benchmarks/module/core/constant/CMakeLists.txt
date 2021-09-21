##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Constants tests
##==================================================================================================
make_unit( core.constant inf.cpp )
make_unit( core.constant minf.cpp )
make_unit( core.constant nan.cpp )
make_unit( core.constant mzero.cpp )
make_unit( core.constant signmask.cpp )
