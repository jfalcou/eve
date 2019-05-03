//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notand.hpp>
#include <cstddef>

#define TYPE()        std::uint8_t
#define FUNCTION()    eve::logical_notand
#define SAMPLES(N)    random<T>(N,0,200),random<T>(N,0,200)

#include "bench.hpp"
