//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>

#define TYPE()        float
#define FUNCTION()    eve::rsqrt
#define SAMPLES(N)    random<T>(N,0.,100.)

#include "bench.hpp"
