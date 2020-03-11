//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <cmath>
#include <eve/wide.hpp>

#define TYPE()        double
#define FUNCTION()    [](double a){return std::cos(a);}    
#define SAMPLES(N)    random<T>(N,0.0, 281474976710656.0)

#include "bench.hpp"
