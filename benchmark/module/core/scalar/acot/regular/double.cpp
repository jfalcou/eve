//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acot.hpp>

#define TYPE()        double
#define FUNCTION()    eve::acot
#define SAMPLES(N)    random<T>(N,-100.,100.)

#include "bench.hpp"
