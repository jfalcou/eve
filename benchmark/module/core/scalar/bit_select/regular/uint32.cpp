//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_select.hpp>

#define TYPE()        uint32_t
#define FUNCTION()    eve::bit_select
#define SAMPLES(N)    random<T>(N,-100.,100.),random<T>(N,-100.,100.),random<T>(N,-100.,100.)

#include "bench.hpp"
