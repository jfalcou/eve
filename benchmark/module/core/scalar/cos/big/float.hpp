//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pi.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<flot>
#define FUNCTION()    eve::cos
#define SAMPLES(N)    random<T>(N,-1000000*Pi<T>(),10000000*Pi<T>())

#include "bench.hpp"
