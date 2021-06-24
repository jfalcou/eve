##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.math.exe                      )
add_custom_target(unit.real.math.scalar.exe               )
add_custom_target(unit.real.math.simd.exe                 )


add_dependencies(unit.real.scalar.exe    unit.real.math.scalar.exe )
add_dependencies(unit.real.simd.exe      unit.real.math.simd.exe   )
add_dependencies(unit.real.math.exe      unit.real.math.scalar.exe )
add_dependencies(unit.real.math.exe      unit.real.math.simd.exe   )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.math"  acos.cpp                  )
make_unit("unit.real.math"  acosd.cpp                 )
make_unit("unit.real.math"  asin.cpp                  )
make_unit("unit.real.math"  asind.cpp                 )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
##make_all_units(ROOT unit.real.math NAME acos                  ARCH scalar simd TYPES ${real_types}    )
##make_all_units(ROOT unit.real.math NAME acosd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acosh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acospi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acot                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acotd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acoth                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acotpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acsc                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acscd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acsch                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME acscpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asec                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asecd                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asech                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asecpi                ARCH scalar simd TYPES ${real_types}    )
##make_all_units(ROOT unit.real.math NAME asin                  ARCH scalar simd TYPES ${real_types}    )
##make_all_units(ROOT unit.real.math NAME asind                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asinh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME asinpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atan                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atand                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atanh                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atanpi                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atan2                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atan2d                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME atan2pi               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cos                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cosd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cospi                 ARCH scalar simd TYPES ${signed_types}  )
make_all_units(ROOT unit.real.math NAME cosh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cot                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cotd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME coth                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cotpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME csc                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cscd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME csch                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME cscpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME deginrad              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME exp                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME exp10                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME expm1                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME expx2                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME log                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME log10                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME log1p                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME log2                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME logspace_add          ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME pow_abs               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME powm1                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME radindeg              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME radinpi               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME rempio2               ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sec                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME secd                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sech                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME secpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sin                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sincos                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinc                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sind                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sindcosd              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinhc                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinhcosh              ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinpi                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinpic                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME sinpicospi            ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME tan                   ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME tand                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME tanh                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math NAME tanpi                 ARCH scalar simd TYPES ${real_types}    )

## ================================================================================================
# Targets that require more RAM to compile

add_custom_target(unit.real.math.heavy.scalar.exe         )
add_custom_target(unit.real.math.heavy.simd.exe           )
add_custom_target(unit.real.math.heavy.exe                )

add_dependencies(unit.real.math.heavy.exe      unit.real.math.heavy.scalar.exe )
add_dependencies(unit.real.math.heavy.exe      unit.real.math.heavy.simd.exe   )
add_dependencies(unit.real.math.scalar.exe     unit.real.math.heavy.scalar.exe )
add_dependencies(unit.real.math.simd.exe       unit.real.math.heavy.simd.exe   )

##=================================================================================================
make_all_units(ROOT unit.real.math.heavy NAME nthroot       ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math.heavy NAME exp2          ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.math.heavy NAME lpnorm        ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT unit.real.math.heavy NAME pow           ARCH scalar simd TYPES ${all_types}     )
make_all_units(ROOT unit.real.math.heavy NAME logspace_sub  ARCH scalar simd TYPES ${real_types}    )
##===================================================================================================
