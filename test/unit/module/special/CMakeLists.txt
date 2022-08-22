##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

add_custom_target(unit.special.exe            )
add_dependencies(unit.exe unit.special.exe    )

make_unit("unit.special" beta.cpp             )
make_unit("unit.special" betainc.cpp          )
make_unit("unit.special" betainc_inv.cpp      )
make_unit("unit.special" dawson.cpp           )
make_unit("unit.special" digamma.cpp          )
make_unit("unit.special" double_factorial.cpp )
make_unit("unit.special" erfc.cpp             )
make_unit("unit.special" erfc_inv.cpp         )
make_unit("unit.special" erf.cpp              )
make_unit("unit.special" erfcx.cpp            )
make_unit("unit.special" erf_inv.cpp          )
make_unit("unit.special" exp_int.cpp          )
make_unit("unit.special" factorial.cpp        )
make_unit("unit.special" gamma_p.cpp          )
make_unit("unit.special" gamma_p_inv.cpp      )
make_unit("unit.special" lambert.cpp          )
make_unit("unit.special" lfactorial.cpp       )
make_unit("unit.special" lgamma.cpp           )
make_unit("unit.special" log_abs_gamma.cpp    )
make_unit("unit.special" log_gamma.cpp        )
make_unit("unit.special" lrising_factorial.cpp)
make_unit("unit.special" omega.cpp            )
make_unit("unit.special" rising_factorial.cpp )
make_unit("unit.special" signgam.cpp          )
make_unit("unit.special" stirling.cpp         )
make_unit("unit.special" tgamma.cpp           )
make_unit("unit.special" zeta.cpp             )
