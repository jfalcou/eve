##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.probas.exe                )
add_custom_target(unit.real.probas.constant.exe       )
add_custom_target(unit.real.probas.constant.scalar.exe)
add_custom_target(unit.real.probas.constant.simd.exe  )
add_custom_target(unit.real.probas.scalar.exe         )
add_custom_target(unit.real.probas.simd.exe           )

add_dependencies(unit.real.scalar.exe          unit.real.probas.scalar.exe          )
add_dependencies(unit.real.simd.exe            unit.real.probas.simd.exe            )
add_dependencies(unit.real.probas.constant.exe unit.real.probas.constant.scalar.exe )
add_dependencies(unit.real.probas.constant.exe unit.real.probas.constant.simd.exe   )
add_dependencies(unit.real.probas.scalar.exe   unit.real.probas.constant.scalar.exe )
add_dependencies(unit.real.probas.simd.exe     unit.real.probas.constant.simd.exe   )
add_dependencies(unit.real.probas.exe          unit.real.probas.constant.exe        )
add_dependencies(unit.real.probas.exe          unit.real.probas.scalar.exe          )
add_dependencies(unit.real.probas.exe          unit.real.probas.simd.exe            )

##==================================================================================================
## Other tests
##==================================================================================================
##add_subdirectory(failure)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
##make_all_units(ROOT unit.real.probas NAME lognormal_distribution          ARCH scalar simd TYPES ${real_types} )
##make_all_units(ROOT unit.real.probas NAME normal_distribution             ARCH scalar simd TYPES ${real_types} )
##make_all_units(ROOT unit.real.probas NAME poisson_distribution            ARCH scalar simd TYPES ${real_types} )
##make_all_units(ROOT unit.real.probas NAME uniform_continuous_distribution ARCH scalar simd TYPES ${real_types} )
##make_all_units(ROOT unit.real.probas NAME uniform_discrete_distribution   ARCH scalar simd TYPES ${real_types} )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.probas"  binomial_distribution.cpp                    )
make_unit("unit.real.probas"  cauchy_distribution.cpp                      )
make_unit("unit.real.probas"  ev_distribution.cpp                          )
make_unit("unit.real.probas"  exponential_distribution.cpp                 )
make_unit("unit.real.probas"  gamma_distribution.cpp                       )
