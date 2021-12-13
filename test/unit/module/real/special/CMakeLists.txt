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
make_unit("unit.real.special"  airy.cpp                    )
make_unit("unit.real.special"  airy_ai.cpp                 )
make_unit("unit.real.special"  airy_bi.cpp                 )
make_unit("unit.real.special"  beta.cpp                    )
make_unit("unit.real.special"  betainc.cpp                 )
make_unit("unit.real.special"  betainc_inv.cpp             )
make_unit("unit.real.special"  cyl_bessel_i0.cpp           )
make_unit("unit.real.special"  cyl_bessel_i1.cpp           )
make_unit("unit.real.special"  cyl_bessel_in.cpp           )
make_unit("unit.real.special"  cyl_bessel_j0.cpp           )
make_unit("unit.real.special"  cyl_bessel_j1.cpp           )
make_unit("unit.real.special"  cyl_bessel_jn.cpp           )
make_unit("unit.real.special"  cyl_bessel_k0.cpp           )
make_unit("unit.real.special"  cyl_bessel_k1.cpp           )
make_unit("unit.real.special"  cyl_bessel_kn.cpp           )
make_unit("unit.real.special"  cyl_bessel_y0.cpp           )
make_unit("unit.real.special"  cyl_bessel_y1.cpp           )
make_unit("unit.real.special"  cyl_bessel_yn.cpp           )
make_unit("unit.real.special"  dawson.cpp                  )
make_unit("unit.real.special"  digamma.cpp                 )
make_unit("unit.real.special"  erf.cpp                     )
make_unit("unit.real.special"  erfc.cpp                    )
make_unit("unit.real.special"  erfcx.cpp                   )
make_unit("unit.real.special"  erf_inv.cpp                 )
make_unit("unit.real.special"  erfc_inv.cpp                )
make_unit("unit.real.special"  exp_int.cpp                 )
make_unit("unit.real.special"  gamma_p.cpp                 )
make_unit("unit.real.special"  gamma_p_inv.cpp             )
make_unit("unit.real.special"  lambert.cpp                 )
make_unit("unit.real.special"  lgamma.cpp                  )
make_unit("unit.real.special"  omega.cpp                   )
make_unit("unit.real.special"  signgam.cpp                 )
make_unit("unit.real.special"  stirling.cpp                )
make_unit("unit.real.special"  tgamma.cpp                  )
make_unit("unit.real.special"  zeta.cpp                    )
