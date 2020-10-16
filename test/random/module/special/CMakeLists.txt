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
add_custom_target(random.special.exe)
add_custom_target(random.special.scalar.exe)
add_custom_target(random.special.simd.exe)
add_dependencies(random.special.exe random.special.scalar.exe)
add_dependencies(random.special.exe random.special.simd.exe)
add_dependencies(random.scalar.exe random.special.scalar.exe)
add_dependencies(random.simd.exe random.special.simd.exe)
add_dependencies(random.exe random.special.exe)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

## make_all_units(ROOT random.special NAME tgamma ARCH scalar simd TYPES ${real_types}    )
## make_all_units(ROOT random.special NAME stirling  ARCH scalar simd TYPES ${real_types}    )
