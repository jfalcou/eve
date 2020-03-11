//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_less_equal.hpp>
#include <cstddef>

#define TYPE()        std::uint8_t
#define FUNCTION()    eve::is_less_equal
#define SAMPLES(N)    random<T>(N,0,200),random<T>(N,0,200)

#include "bench.hpp"
