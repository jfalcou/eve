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
make_unit("unit.real.math"  acosh.cpp                 )
make_unit("unit.real.math"  acospi.cpp                )
make_unit("unit.real.math"  acot.cpp                  )
make_unit("unit.real.math"  acotd.cpp                 )
make_unit("unit.real.math"  acoth.cpp                 )
make_unit("unit.real.math"  acotpi.cpp                )
make_unit("unit.real.math"  acsc.cpp                  )
make_unit("unit.real.math"  acscd.cpp                 )
make_unit("unit.real.math"  acsch.cpp                 )
make_unit("unit.real.math"  acscpi.cpp                )
make_unit("unit.real.math"  asec.cpp                  )
make_unit("unit.real.math"  asecd.cpp                 )
make_unit("unit.real.math"  asech.cpp                 )
make_unit("unit.real.math"  asecpi.cpp                )
make_unit("unit.real.math"  asin.cpp                  )
make_unit("unit.real.math"  asind.cpp                 )
make_unit("unit.real.math"  asinh.cpp                 )
make_unit("unit.real.math"  asinpi.cpp                )
make_unit("unit.real.math"  atan.cpp                  )
make_unit("unit.real.math"  atand.cpp                 )
make_unit("unit.real.math"  atanh.cpp                 )
make_unit("unit.real.math"  atanpi.cpp                )
make_unit("unit.real.math"  atan2.cpp                 )
make_unit("unit.real.math"  atan2d.cpp                )
make_unit("unit.real.math"  atan2pi.cpp               )
make_unit("unit.real.math"  cos.cpp                   )
make_unit("unit.real.math"  cosd.cpp                  )
make_unit("unit.real.math"  cosh.cpp                  )
make_unit("unit.real.math"  cospi.cpp                 )
make_unit("unit.real.math"  cot.cpp                   )
make_unit("unit.real.math"  cotd.cpp                  )
make_unit("unit.real.math"  coth.cpp                  )
make_unit("unit.real.math"  cotpi.cpp                 )
make_unit("unit.real.math"  csc.cpp                   )
make_unit("unit.real.math"  cscd.cpp                  )
make_unit("unit.real.math"  csch.cpp                  )
make_unit("unit.real.math"  cscpi.cpp                 )
make_unit("unit.real.math"  deginrad.cpp              )
make_unit("unit.real.math"  exp.cpp                   )
make_unit("unit.real.math"  exp10.cpp                 )
make_unit("unit.real.math"  exp2.cpp                  )

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
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
