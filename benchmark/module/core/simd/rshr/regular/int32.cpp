//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshr.hpp>
#include <eve/wide.hpp>

#define TYPE()        eve::wide<int32_t>
#define FUNCTION()    eve::rshr
#define SAMPLES(N)    random<T>(N,-100.,100.),random<int>(N, -int(sizeof(typename TYPE()::value_type)+1), int(sizeof(typename TYPE()::value_type)-1))

#include "bench.hpp"
