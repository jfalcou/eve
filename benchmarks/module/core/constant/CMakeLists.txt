##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
