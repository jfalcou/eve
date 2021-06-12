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
make_unit("unit.real.special"  beta.cpp                    )
make_unit("unit.real.special"  betainc.cpp                 )
make_unit("unit.real.special"  betainc_inv.cpp             )
make_unit("unit.real.special"  dawson.cpp                  )
make_unit("unit.real.special"  digamma.cpp                 )
make_unit("unit.real.special"  erf.cpp                     )
make_unit("unit.real.special"  erfc.cpp                    )
make_unit("unit.real.special"  erfcx.cpp                   )
make_unit("unit.real.special"  erf_inv.cpp                 )
make_unit("unit.real.special"  exp_int.cpp                 )
make_unit("unit.real.special"  gamma_p.cpp                 )
make_unit("unit.real.special"  gamma_pinv.cpp              )
make_unit("unit.real.special"  lgamma.cpp                  )
make_unit("unit.real.special"  tgamma.cpp                  )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

make_all_units(ROOT unit.real.special NAME erfc_inv      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME signgam       ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME stirling      ARCH scalar simd TYPES ${real_types} )
make_all_units(ROOT unit.real.special NAME zeta          ARCH scalar simd TYPES ${real_types} )
