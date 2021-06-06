##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.special.exe       )
add_custom_target(unit.real.special.scalar.exe)
add_custom_target(unit.real.special.simd.exe  )

add_dependencies(unit.real.scalar.exe   unit.real.special.scalar.exe )
add_dependencies(unit.real.simd.exe     unit.real.special.simd.exe   )
add_dependencies(unit.real.special.exe  unit.real.special.scalar.exe )
add_dependencies(unit.real.special.exe  unit.real.special.simd.exe   )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.special"  gamma_p.cpp                 )
make_unit("unit.real.special"  gamma_pinv.cpp                 )
make_unit("unit.real.special"  lgamma.cpp                  )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

make_all_units(ROOT unit.real.special NAME beta          ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME betainc       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME betainc_inv   ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME dawson        ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME digamma       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME erf           ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME erfc          ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME erfcx         ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME erf_inv       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME erfc_inv      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME exp_int       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_j0 ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_j1 ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_j  ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME gamma_p       ARCH scalar simd TYPES ${real_types} )
##make_all_units(ROOT unit.real.special NAME lgamma        ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME signgam       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME stirling      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME tgamma        ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_y  ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_y0 ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME cyl_bessel_y1 ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME zeta          ARCH scalar simd TYPES ${real_types} )
