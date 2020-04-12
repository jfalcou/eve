##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Hyperbolic function unit tests
##==================================================================================================
make_all_units(ROOT core NAME acosh     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME acoth     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME acsch     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME asech     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME asinh     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME atanh     ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME cosh      ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME coth      ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME csch      ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME sech      ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME sinh      ARCH scalar simd TYPES ${real_types})
#sinhc
make_all_units(ROOT core NAME sinhcosh  ARCH scalar simd TYPES ${real_types})
make_all_units(ROOT core NAME tanh      ARCH scalar simd TYPES ${real_types})

##==================================================================================================
## Hyperbolic meta-target
##==================================================================================================
add_custom_target(core.hyperbolic.unit)
add_custom_target(core.hyperbolic.simd.unit)
add_custom_target(core.hyperbolic.scalar.unit)

add_dependencies(core.hyperbolic.unit core.hyperbolic.simd.unit  )
add_dependencies(core.hyperbolic.unit core.hyperbolic.scalar.unit)

add_dependencies(core.hyperbolic.scalar.unit core.acosh.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.acoth.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.acsch.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.asech.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.asinh.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.atanh.regular.scalar.unit     )
add_dependencies(core.hyperbolic.scalar.unit core.cosh.regular.scalar.unit      )
add_dependencies(core.hyperbolic.scalar.unit core.coth.regular.scalar.unit      )
add_dependencies(core.hyperbolic.scalar.unit core.csch.regular.scalar.unit      )
add_dependencies(core.hyperbolic.scalar.unit core.sech.regular.scalar.unit      )
add_dependencies(core.hyperbolic.scalar.unit core.sinh.regular.scalar.unit      )
add_dependencies(core.hyperbolic.scalar.unit core.sinhcosh.regular.scalar.unit  )
add_dependencies(core.hyperbolic.scalar.unit core.tanh.regular.scalar.unit      )

add_dependencies(core.hyperbolic.simd.unit core.acosh.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.acoth.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.acsch.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.asech.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.asinh.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.atanh.regular.simd.unit     )
add_dependencies(core.hyperbolic.simd.unit core.cosh.regular.simd.unit      )
add_dependencies(core.hyperbolic.simd.unit core.coth.regular.simd.unit      )
add_dependencies(core.hyperbolic.simd.unit core.csch.regular.simd.unit      )
add_dependencies(core.hyperbolic.simd.unit core.sech.regular.simd.unit      )
add_dependencies(core.hyperbolic.simd.unit core.sinh.regular.simd.unit      )
add_dependencies(core.hyperbolic.simd.unit core.sinhcosh.regular.simd.unit  )
add_dependencies(core.hyperbolic.simd.unit core.tanh.regular.simd.unit      )
