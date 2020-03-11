//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notor.hpp>
#include <cstddef>

#define TYPE()        std::int8_t
#define FUNCTION()    eve::logical_notor
#define SAMPLES(N)    random<T>(N,-100,100),random<T>(N,-100,100)

#include "bench.hpp"
