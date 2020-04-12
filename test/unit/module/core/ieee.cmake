##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## IEEE754 function unit tests
##==================================================================================================

make_all_units(ROOT core NAME bitofsign             ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME eps                   ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME exponent              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME exponentbits          ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME frexp                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME ifrexp                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME ldexp                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME mantissa              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME nb_values             ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME nextafter             ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT core NAME two_split             ARCH scalar simd TYPES ${real_types}    )
# two_add
# two_prod
make_all_units(ROOT core NAME ulpdist               ARCH scalar simd TYPES ${all_types}     )

##==================================================================================================
## IEEE754 meta-target
##==================================================================================================
add_custom_target(core.ieee.unit)
add_custom_target(core.ieee.simd.unit)
add_custom_target(core.ieee.scalar.unit)

add_dependencies(core.ieee.unit core.ieee.simd.unit  )
add_dependencies(core.ieee.unit core.ieee.scalar.unit)

add_dependencies(core.ieee.scalar.unit core.bitofsign.regular.scalar.unit     )
add_dependencies(core.ieee.scalar.unit core.eps.regular.scalar.unit           )
add_dependencies(core.ieee.scalar.unit core.exponent.regular.scalar.unit      )
add_dependencies(core.ieee.scalar.unit core.exponentbits.regular.scalar.unit  )
add_dependencies(core.ieee.scalar.unit core.frexp.regular.scalar.unit         )
add_dependencies(core.ieee.scalar.unit core.frexp.pedantic.scalar.unit        )
add_dependencies(core.ieee.scalar.unit core.frexp.raw.scalar.unit             )
add_dependencies(core.ieee.scalar.unit core.ifrexp.regular.scalar.unit        )
add_dependencies(core.ieee.scalar.unit core.ifrexp.pedantic.scalar.unit       )
add_dependencies(core.ieee.scalar.unit core.ifrexp.raw.scalar.unit            )
add_dependencies(core.ieee.scalar.unit core.ldexp.pedantic.scalar.unit        )
add_dependencies(core.ieee.scalar.unit core.ldexp.regular.scalar.unit         )
add_dependencies(core.ieee.scalar.unit core.mantissa.regular.scalar.unit      )
add_dependencies(core.ieee.scalar.unit core.nb_values.regular.scalar.unit     )
add_dependencies(core.ieee.scalar.unit core.nextafter.regular.scalar.unit     )
add_dependencies(core.ieee.scalar.unit core.nextafter.pedantic.scalar.unit    )
add_dependencies(core.ieee.scalar.unit core.signnz.regular.scalar.unit        )
add_dependencies(core.ieee.scalar.unit core.two_split.regular.scalar.unit     )
add_dependencies(core.ieee.scalar.unit core.ulpdist.regular.scalar.unit       )

add_dependencies(core.ieee.simd.unit core.bitofsign.regular.simd.unit     )
add_dependencies(core.ieee.simd.unit core.eps.regular.simd.unit           )
add_dependencies(core.ieee.simd.unit core.exponent.regular.simd.unit      )
add_dependencies(core.ieee.simd.unit core.exponentbits.regular.simd.unit  )
add_dependencies(core.ieee.simd.unit core.frexp.regular.simd.unit         )
add_dependencies(core.ieee.simd.unit core.frexp.pedantic.simd.unit        )
add_dependencies(core.ieee.simd.unit core.frexp.raw.simd.unit             )
add_dependencies(core.ieee.simd.unit core.ifrexp.regular.simd.unit        )
add_dependencies(core.ieee.simd.unit core.ifrexp.pedantic.simd.unit       )
add_dependencies(core.ieee.simd.unit core.ifrexp.raw.simd.unit            )
add_dependencies(core.ieee.simd.unit core.ldexp.pedantic.simd.unit        )
add_dependencies(core.ieee.simd.unit core.ldexp.regular.simd.unit         )
add_dependencies(core.ieee.simd.unit core.mantissa.regular.simd.unit      )
add_dependencies(core.ieee.simd.unit core.nb_values.regular.simd.unit     )
add_dependencies(core.ieee.simd.unit core.nextafter.regular.simd.unit     )
add_dependencies(core.ieee.simd.unit core.nextafter.pedantic.simd.unit    )
add_dependencies(core.ieee.simd.unit core.signnz.regular.simd.unit        )
add_dependencies(core.ieee.simd.unit core.two_split.regular.simd.unit     )
add_dependencies(core.ieee.simd.unit core.ulpdist.regular.simd.unit       )
