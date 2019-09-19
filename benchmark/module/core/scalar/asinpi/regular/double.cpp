//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>

#define TYPE()        double
#define FUNCTION()    eve::asinpi
#define SAMPLES(N)    random<T>(N,-1.,1.)

#include "bench.hpp"
