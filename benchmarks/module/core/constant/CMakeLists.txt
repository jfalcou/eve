##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Constants tests
##==================================================================================================
make_unit( core.constant inf.cpp )
make_unit( core.constant minf.cpp )
make_unit( core.constant nan.cpp )
make_unit( core.constant mzero.cpp )
make_unit( core.constant signmask.cpp )
