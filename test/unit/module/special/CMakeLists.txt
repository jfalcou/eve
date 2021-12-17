##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.special.exe           )
add_dependencies(unit.exe unit.special.exe   )

make_unit("unit.special" beta.cpp          )
make_unit("unit.special" betainc.cpp       )
make_unit("unit.special" betainc_inv.cpp   )
make_unit("unit.special" dawson.cpp        )
make_unit("unit.special" digamma.cpp       )
make_unit("unit.special" erfc.cpp          )
make_unit("unit.special" erfc_inv.cpp      )
make_unit("unit.special" erf.cpp           )
make_unit("unit.special" erfcx.cpp         )
make_unit("unit.special" erf_inv.cpp       )
make_unit("unit.special" exp_int.cpp       )
make_unit("unit.special" gamma_p.cpp       )
make_unit("unit.special" gamma_p_inv.cpp   )
make_unit("unit.special" lambert.cpp       )
make_unit("unit.special" lgamma.cpp        )
make_unit("unit.special" omega.cpp         )
make_unit("unit.special" signgam.cpp       )
make_unit("unit.special" stirling.cpp      )
make_unit("unit.special" tgamma.cpp        )
make_unit("unit.special" zeta.cpp          )
