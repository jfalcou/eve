//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::raw_(eve::pow_abs)
#define SAMPLES(N)    random<T>(N,0.,100.),random<T>(N,-100.,100.)

#include "bench.hpp"
