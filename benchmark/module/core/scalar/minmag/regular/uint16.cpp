//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>

#define TYPE()        uint16_t
#define FUNCTION()    eve::minmag
#define SAMPLES(N)    random<T>(N,-100.,100.),random<T>(N,-100.,100.)

#include "bench.hpp"
