//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notor.hpp>
#include <eve/wide.hpp>
#include <cstddef>

#define TYPE()        eve::wide<std::uint32_t>
#define FUNCTION()    eve::bit_notor
#define SAMPLES(N)    random<T>(N,0,10000),random<T>(N,0,10000)

#include "bench.hpp"
