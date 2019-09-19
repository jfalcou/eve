//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nan.hpp>

#define TYPE()        double
#define FUNCTION()    eve::is_nan
#define SAMPLES(N)    random<T>(N,-100.,100.)

#include "bench.hpp"
