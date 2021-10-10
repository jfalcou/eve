##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(random.real.special.exe)
add_custom_target(random.real.special.scalar.exe)
add_custom_target(random.real.special.simd.exe)
add_dependencies(random.real.special.exe random.real.special.scalar.exe)
add_dependencies(random.real.special.exe random.real.special.simd.exe)
add_dependencies(random.real.scalar.exe random.real.special.scalar.exe)
add_dependencies(random.real.simd.exe random.real.special.simd.exe)
add_dependencies(random.real.exe random.real.special.exe)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

## make_all_units(ROOT random.real.special NAME tgamma ARCH scalar simd TYPES ${real_types}    )
## make_all_units(ROOT random.real.special NAME stirling  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT random.real.special NAME cyl_bessel_j0  ARCH scalar simd TYPES ${real_types}    )
