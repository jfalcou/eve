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
#include <eve/wide.hpp>

#define TYPE()        eve::wide<double>; 
#define FUNCTION()    eve::exp2
#define SAMPLES(N)    random<T>(N,-1000.,1000.)

#include "bench.hpp"
