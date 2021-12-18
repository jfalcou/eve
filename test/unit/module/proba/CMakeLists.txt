##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.proba.exe           )
add_dependencies(unit.exe unit.proba.exe   )

make_unit( "unit.proba" binomial_distribution.cpp           )
make_unit( "unit.proba" cauchy_distribution.cpp             )
make_unit( "unit.proba" ev_distribution.cpp                 )
make_unit( "unit.proba" exponential_distribution.cpp        )
make_unit( "unit.proba" gamma_distribution.cpp              )
make_unit( "unit.proba" lognormal_distribution.cpp          )
make_unit( "unit.proba" normal_distribution.cpp             )
make_unit( "unit.proba" poisson_distribution.cpp            )
make_unit( "unit.proba" uniform_continuous_distribution.cpp )
make_unit( "unit.proba" uniform_discrete_distribution.cpp   )
