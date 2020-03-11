//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nltz.hpp>
#include <cstddef>

#define TYPE()        std::uint16_t
#define FUNCTION()    eve::is_nltz
#define SAMPLES(N)    random<T>(N,0,10000)

#include "bench.hpp"
