//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <cstddef>

#define TYPE()        std::uint32_t
#define FUNCTION()    eve::max
#define SAMPLES(N)    random<T>(N,0,10000),random<T>(N,0,10000)

#include "bench.hpp"
