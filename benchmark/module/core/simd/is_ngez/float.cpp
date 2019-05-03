//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ngez.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::is_ngez
#define SAMPLES(N)    random<T>(N,-100.f,100.f)

#include "bench.hpp"

