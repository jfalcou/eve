//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/wide.hpp>

TTS_CASE("Check splatting constructor for arithmetic wide")
{
  EVE_VALUE base = 42;
  EVE_TYPE  simd(base);
  EVE_TYPE  ref;

  for(std::ptrdiff_t i = 0; i < simd.size(); ++i)
    ref.set(i, base);

  TTS_EQUAL(simd, ref);
}
