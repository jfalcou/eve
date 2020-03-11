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
#define FUNCTION()    [](double a){return std::tan(a);}    
#define SAMPLES(N)    random<T>(N,0.0, 1.0e38)

#include "bench.hpp"
