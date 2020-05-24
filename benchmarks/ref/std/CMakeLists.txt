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
make_all_benchs(ROOT std NAME abs       ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME acos      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME asin      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME atan      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME bit_ceil  ARCH scalar TYPES ${uint_types} )
make_all_benchs(ROOT std NAME bit_floor ARCH scalar TYPES ${uint_types} )
make_all_benchs(ROOT std NAME cbrt      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME ceil      ARCH scalar TYPES ${all_types}  )
make_all_benchs(ROOT std NAME copysign  ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME cos       ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME cosh      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME floor     ARCH scalar TYPES ${all_types}  )
make_all_benchs(ROOT std NAME fma       ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME frexp     ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME hypot     ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME ldexp     ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME popcount  ARCH scalar TYPES ${uint_types} )
make_all_benchs(ROOT std NAME sin       ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME sinh      ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME tan       ARCH scalar TYPES ${real_types} )
make_all_benchs(ROOT std NAME tanh      ARCH scalar TYPES ${real_types} )