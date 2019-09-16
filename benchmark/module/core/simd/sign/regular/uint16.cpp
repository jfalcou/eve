//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<uint16_t>
#define FUNCTION()    eve::sign
#define SAMPLES(N)    random<T>(N,-100.,100.)

#include "bench.hpp"
