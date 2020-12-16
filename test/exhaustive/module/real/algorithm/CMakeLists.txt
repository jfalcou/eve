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
add_custom_target(exhaustive.real.algorithm.exe)
add_custom_target(exhaustive.real.algorithm.scalar.exe)
add_custom_target(exhaustive.real.algorithm.simd.exe)
add_dependencies(exhaustive.real.algorithm.exe exhaustive.real.algorithm.scalar.exe)
add_dependencies(exhaustive.real.algorithm.exe exhaustive.real.algorithm.simd.exe)
add_dependencies(exhaustive.real.scalar.exe exhaustive.real.algorithm.scalar.exe)
add_dependencies(exhaustive.real.simd.exe exhaustive.real.algorithm.simd.exe)
add_dependencies(exhaustive.real.exe exhaustive.real.algorithm.exe)

##==================================================================================================
## Algorithms function exhaustive tests
##==================================================================================================
#empty yet