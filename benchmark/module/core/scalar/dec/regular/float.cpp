//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>

#define TYPE()        float
#define FUNCTION()    eve::dec
#define SAMPLES(N)    random<T>(N,-100.f,100.f)

#include "bench.hpp"
