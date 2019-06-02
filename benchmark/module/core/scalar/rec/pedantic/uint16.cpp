//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <cstddef>

#define TYPE()        std::uint16_t
#define FUNCTION()    eve::rec[eve::pedantic_]
#define SAMPLES(N)    random<T>(N,0,10000)

#include "bench.hpp"
