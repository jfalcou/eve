//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <cmath>
#include <eve/wide.hpp>

#define TYPE()        float
#define FUNCTION()    [](float a){return std::cos(a);}
#define SAMPLES(N)    random<T>(N,0.0f, 281474976710656.0f)

#include "bench.hpp"
