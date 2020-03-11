//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosd.hpp>
#include <eve/wide.hpp>
#include <eve/constant/pi.hpp>

#define TYPE()        float
#define FUNCTION()    eve::restricted_(eve::cosd)
#define SAMPLES(N)    random<T>(N,-0.25*eve::Pi<T>(),0.25*eve::Pi<T>())

#include "bench.hpp"
