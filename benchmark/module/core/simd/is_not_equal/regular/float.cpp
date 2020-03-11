//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_equal.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<float>
#define FUNCTION()    eve::is_not_equal
#define SAMPLES(N)    random<T>(N,-100.f,100.f),random<T>(N,-100.f,100.f)

#include "bench.hpp"

