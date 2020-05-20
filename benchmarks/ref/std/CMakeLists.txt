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
add_custom_target(std.bench)
add_custom_target(std.scalar.bench)
add_custom_target(std.simd.bench)
add_dependencies(std.bench std.scalar.bench)
add_dependencies(std.bench std.simd.bench)
add_dependencies(bench std.bench)

##==================================================================================================
## List of tests
##==================================================================================================
make_all_benchs(ROOT std NAME acos  ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME asin  ARCH scalar TYPES ${real_types} )
