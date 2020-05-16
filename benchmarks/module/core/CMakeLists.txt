##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(core.bench)
add_custom_target(core.scalar.bench)
add_custom_target(core.simd.bench)
add_dependencies(core.bench core.scalar.bench)
add_dependencies(core.bench core.simd.bench)
add_dependencies(bench core.bench)

##==================================================================================================
## List of tests
##==================================================================================================
make_all_benchs(ROOT core NAME acos  ARCH scalar simd TYPES ${real_types} )
