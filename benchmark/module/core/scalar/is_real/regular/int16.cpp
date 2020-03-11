//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_real.hpp>
#include <cstddef>

#define TYPE()        std::int16_t
#define FUNCTION()    eve::is_real
#define SAMPLES(N)    random<T>(N,-100,100)

#include "bench.hpp"
