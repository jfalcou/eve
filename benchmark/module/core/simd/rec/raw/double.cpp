//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<double>
#define FUNCTION()    eve::raw_(eve::rec)
#define SAMPLES(N)    random<T>(N,1.,1000.)

#include "bench.hpp"

