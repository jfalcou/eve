//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <cmath>


#define TYPE()        float
#define FUNCTION()    [](float x, std::int64_t n)   \
  {                                                 \
    return std::ldexp(x, n);                        \
  }                                                 \
/**/
#define SAMPLES(N)    random<T>(N,-700.,700.), random<std::int64_t>(N,-100, 100)

#include "bench.hpp"
