##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(bench.algorithm.exe)

##==================================================================================================
## Algoritms function bench tests
##==================================================================================================
make_all_benchs(ROOT bench.algorithm NAME all    ARCH scalar simd TYPES ${all_types})
make_all_benchs(ROOT bench.algorithm NAME any    ARCH scalar simd TYPES ${all_types})
make_all_benchs(ROOT bench.algorithm NAME nbtrue ARCH scalar simd TYPES ${all_types})
make_all_benchs(ROOT bench.algorithm NAME none   ARCH scalar simd TYPES ${all_types})
