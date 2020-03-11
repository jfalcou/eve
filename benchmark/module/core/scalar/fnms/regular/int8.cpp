//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnms.hpp>
#include <cstddef>

#define TYPE()        std::int8_t
#define FUNCTION()    eve::fnms
#define SAMPLES(N)    random<T>(N,-100,100),random<T>(N,-100,100),random<T>(N,-100,100)

#include "bench.hpp"
