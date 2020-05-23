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
make_all_units(ROOT core.constant NAME nan       ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core.constant NAME inf       ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core.constant NAME minf      ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core.constant NAME mzero     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core.constant NAME signmask  ARCH scalar simd TYPES ${all_types} )

