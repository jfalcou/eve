//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shr.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<uint16_t>
#define FUNCTION()    eve::bit_shr
#define SAMPLES(N)    random<T>(N,-100.,100.),random<int>(N, 0UL, sizeof(typename TYPE()::value_type)-1)

#include "bench.hpp"
