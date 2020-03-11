//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscd.hpp>

#define TYPE()        float
#define FUNCTION()    eve::acscd
#define SAMPLES(N)    random<T>(N,1.,100.)

#include "bench.hpp"
