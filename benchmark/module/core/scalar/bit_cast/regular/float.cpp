//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_cast.hpp>

#define TYPE()        float
#define FUNCTION()    eve::bit_cast
#define SAMPLES(N)    random<T>(N,-100.f,100.f),random<T>(N,-100.f,100.f)

#include "bench.hpp"
