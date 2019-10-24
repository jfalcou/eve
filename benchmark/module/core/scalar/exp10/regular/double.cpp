//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>

#define TYPE()        double
#define FUNCTION()    eve::exp10
#define SAMPLES(N)    random<T>(N,-300.,300.)

#include "bench.hpp"
