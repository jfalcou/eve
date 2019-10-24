//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>

#define TYPE()        float
#define FUNCTION()    eve::exp2
#define SAMPLES(N)    random<T>(N,-100.0f,100.0f)

#include "bench.hpp"
