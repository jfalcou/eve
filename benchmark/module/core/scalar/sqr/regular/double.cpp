//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>

#define TYPE()        double
#define FUNCTION()    eve::sqr
#define SAMPLES(N)    random<T>(N,0.,100.)

#include "bench.hpp"
