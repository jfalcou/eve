//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/wide.hpp>
#include <eve/constant/pi.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::big_(eve::tan)
#define SAMPLES(N)    random<T>(N,0.0f, 1.0e38f)

#include "bench.hpp"
