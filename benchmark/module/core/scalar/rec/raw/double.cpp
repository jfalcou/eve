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

#define TYPE()        double
#define FUNCTION()    eve::rec[eve::raw_]
#define SAMPLES(N)    random<T>(N,1.,1000.)

#include "bench.hpp"
