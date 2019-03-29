##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## scalar benchmarks
list_benchs("scalar/bitwise_and" "core" ${all_types})

##==================================================================================================
## SIMD< benchmarks
list_benchs("simd/bitwise_and" "core" ${all_types})
