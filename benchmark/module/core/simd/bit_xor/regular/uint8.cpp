//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_xor.hpp>
#include <eve/wide.hpp>
#include <cstddef>

#define TYPE()        eve::wide<std::uint8_t>
#define FUNCTION()    eve::bit_xor
#define SAMPLES(N)    random<T>(N,0,200),random<T>(N,0,200)

#include "bench.hpp"
