##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(bench.bessel.exe)

##==================================================================================================
## Special function bench tests
##==================================================================================================

make_all_benchs(ROOT bench.special NAME cyl_bessel_j0 TYPES ${real_types} )
make_all_benchs(ROOT bench.special NAME cyl_bessel_j1 TYPES ${real_types} )
make_all_benchs(ROOT bench.special NAME cyl_bessel_jn TYPES ${real_types} )
make_all_benchs(ROOT bench.special NAME cyl_bessel_y0 TYPES ${real_types} )