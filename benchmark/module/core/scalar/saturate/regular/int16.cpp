//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>

#define TYPE()        int16_t
#define FUNCTION()    eve::saturate[eve::as(int8_t())]
#define SAMPLES(N)    random<T>(N,-1000.,1000.)

#include "bench.hpp"
