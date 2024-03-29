##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(bench.math.exe)

##==================================================================================================
## Elementwise function bench tests
##==================================================================================================
make_all_benchs(ROOT bench.math NAME acos        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acosd       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acosh       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acospi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acot        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acotd       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acoth       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acotpi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acsc        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acscd       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acsch       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME acscpi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asec        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asecd       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asech       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asecpi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asin        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asind       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asinh       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME asinpi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atan        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atand       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atanh       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atanpi      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atan2       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atan2d      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME atan2pi     TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cos         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cosd        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cospi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cosh        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cot         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cotd        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME coth        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cotpi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME csc         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cscd        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME csch        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME cscpi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME deginrad    TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME exp         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME exp10       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME exp2        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME expm1       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME log         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME log10       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME log1p       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME log2        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME pow         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME pow_abs     TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME radindeg    TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME radinpi     TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME rempio2     TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sec         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME secd        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sech        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME secpi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sin         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sincos      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sind        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sindcosd    TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sinh        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sinhcosh    TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sinpi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME sinpicospi  TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME tan         TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME tand        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME tanh        TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME tanpi       TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME horner      TYPES ${real_types}    )
make_all_benchs(ROOT bench.math NAME reverse_horner      TYPES ${real_types}    )
