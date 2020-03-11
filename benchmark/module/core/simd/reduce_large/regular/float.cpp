//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce_large.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::reduce_large
#define SAMPLES(N)    random<T>(N,0.0f,8388608.0f)
//10000000000.0f)

#include "bench.hpp"
