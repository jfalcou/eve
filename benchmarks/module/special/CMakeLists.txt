##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(bench.special.exe)

##==================================================================================================
## Special function bench tests
##==================================================================================================

### TEMPORARY MEASURE
make_all_benchs(ROOT bench.special NAME beta               TYPES ${real_types}    )
make_all_benchs(ROOT bench.special NAME cyl_bessel_j0      TYPES ${real_types}    )
make_all_benchs(ROOT bench.special NAME cyl_bessel_j1      TYPES ${real_types}    )
make_all_benchs(ROOT bench.special NAME erf                TYPES ${real_types}    )
make_all_benchs(ROOT bench.special NAME erfc               TYPES ${real_types}    )
make_all_benchs(ROOT bench.special NAME erfcx              TYPES ${real_types}    )
##make_all_benchs(ROOT bench.special NAME tgamma             TYPES ${real_types}    )
##make_all_benchs(ROOT bench.special NAME stirling           TYPES ${real_types}    )
### TEMPORARY MEASURE
