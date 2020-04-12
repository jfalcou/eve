##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Other tests
##==================================================================================================
add_subdirectory(constant)
add_subdirectory(failure)

include(arithmetic)
include(bits)
include(comparisons)
include(conversion)
include(exponential)
include(hyperbolic)
include(ieee)
include(invtrigonometric)
include(logical)
include(operators)
include(predicates)
include(reduction)
include(rounding)
include(swar)
include(trigonometric)

##==================================================================================================
## Elementwise function unit tests
##==================================================================================================
make_all_units(ROOT core NAME horn                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME horn1                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME indeg                 ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME inpi                  ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME reduce                ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME reduce_fast           ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME reduce_large          ARCH scalar simd TYPES ${real_types}    )
make_all_units(ROOT core NAME reduce_medium         ARCH scalar simd TYPES ${real_types}    )
