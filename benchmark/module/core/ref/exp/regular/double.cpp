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


#define TYPE()        double
#define FUNCTION()    [](double x)              \
  {                                             \
    return std::exp(x);                         \
  }                                             \
/**/
#define SAMPLES(N)    random<T>(N,-700.,700.)

#include "bench.hpp"
