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
add_custom_target(random.real.algorithm.exe)
add_custom_target(random.real.algorithm.scalar.exe)
add_custom_target(random.real.algorithm.simd.exe)
add_dependencies(random.real.algorithm.exe random.real.algorithm.scalar.exe)
add_dependencies(random.real.algorithm.exe random.real.algorithm.simd.exe)
add_dependencies(random.real.scalar.exe random.real.algorithm.scalar.exe)
add_dependencies(random.real.simd.exe random.real.algorithm.simd.exe)
add_dependencies(random.real.exe random.real.algorithm.exe)

##==================================================================================================
## Algoritms function random tests
##==================================================================================================
#empty yet