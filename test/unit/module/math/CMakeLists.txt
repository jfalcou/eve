##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2019 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(math.unit)
add_custom_target(math.scalar.unit)
add_custom_target(math.simd.unit)
add_dependencies(math.unit math.scalar.unit)
add_dependencies(math.unit math.simd.unit)

##==================================================================================================
## Other tests
##==================================================================================================
#dd_subdirectory(failure)
#add_subdirectory(constant)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT math NAME acos                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acosd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acosh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acospi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acot                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acotd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acoth                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acotpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acsc                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acscd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acsch                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME acscpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asec                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asecd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asech                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asecpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asin                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asind                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asinh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME asinpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atan                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atand                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atanh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atanpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atan2                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atan2d                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME atan2pi               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cos                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cosd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cospi                 ARCH scalar simd TYPES ${signed_types}  )
make_all_units(ROOT math NAME cosh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cot                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cotd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME coth                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cotpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME csc                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cscd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME csch                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME cscpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME deginrad              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME exp                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME exp10                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME exp2                  ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT math NAME expm1                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME log                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME log10                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME log1p                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME log2                  ARCH scalar simd TYPES ${real_types}    )
### TEMPORARY MEASURE
### make_all_units(ROOT math NAME pow                   ARCH scalar simd TYPES ${all_types}    )
### TEMPORARY MEASURE
make_all_units(ROOT math NAME pow_abs               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME radindeg              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME radinpi               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME rempio2               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sec                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME secd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sech                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME secpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sin                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sincos                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sind                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sindcosd              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sinh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sinhcosh              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sinpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME sinpicospi            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME tan                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME tand                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME tanh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT math NAME tanpi                 ARCH scalar simd TYPES ${real_types}    )
