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
#include <eve/constant/pi.hpp>
#include <eve/wide.hpp>

#define TYPE()        float
#define FUNCTION()    [](float a){return std::tan(a);}   
#define SAMPLES(N)    random<T>(N,0.0f,1.0e38f)

#include "bench.hpp"
