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
#include <eve/constant/pi.hpp>
#include <eve/wide.hpp>

#define TYPE()        double
#define FUNCTION()    [](double a){return std::cos(a);}  
#define SAMPLES(N)    random<T>(N,-1000*eve::Pi<T>(),1000*eve::Pi<T>())

#include "bench.hpp"
