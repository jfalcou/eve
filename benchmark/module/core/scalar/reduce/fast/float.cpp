//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce_fast.hpp>

#define TYPE()        float
#define FUNCTION()    eve::reduce_fast
#define SAMPLES(N)    random<T>(N,0.0f, 200.0f)

#include "bench.hpp"
