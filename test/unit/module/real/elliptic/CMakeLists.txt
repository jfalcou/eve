##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.elliptic.exe       )
add_custom_target(unit.real.elliptic.scalar.exe)
add_custom_target(unit.real.elliptic.simd.exe  )

add_dependencies(unit.real.scalar.exe   unit.real.elliptic.scalar.exe )
add_dependencies(unit.real.simd.exe     unit.real.elliptic.simd.exe   )
add_dependencies(unit.real.elliptic.exe unit.real.elliptic.scalar.exe )
add_dependencies(unit.real.elliptic.exe unit.real.elliptic.simd.exe   )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.elliptic"  ellint_1.cpp                  )
make_unit("unit.real.elliptic"  ellint_2.cpp                  )
#make_unit("unit.real.elliptic"  ellint_3.cpp                  )
make_unit("unit.real.elliptic"  ellint_d.cpp                  )
make_unit("unit.real.elliptic"  ellint_rc.cpp                 )
make_unit("unit.real.elliptic"  ellint_rd.cpp                 )
make_unit("unit.real.elliptic"  ellint_rf.cpp                 )
make_unit("unit.real.elliptic"  ellint_rg.cpp                 )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================

#make_all_units(ROOT unit.real.elliptic NAME am                   ARCH scalar simd TYPES ${real_types}    )
# make_all_units(ROOT unit.real.elliptic NAME ellint_3             ARCH scalar simd TYPES ${real_types}    )
# make_all_units(ROOT unit.real.elliptic NAME heuman_lambda        ARCH scalar simd TYPES ${real_types}    )
# make_all_units(ROOT unit.real.elliptic NAME jacobi_real.elliptic      ARCH scalar simd TYPES ${real_types}    )
