//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::reduce
#define SAMPLES(N)    random<T>(N,0.0f,1.0e38f)

#include "bench.hpp"
