//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>

#define TYPE()        int8_t
#define FUNCTION()    eve::if_else
#define SAMPLES(N)    random<T>(N,0.,1.),random<T>(N,-100.,100.),random<T>(N,-100.,100.)

#include "bench.hpp"
