//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE("Check enumerating constructor for wide of logical")
{
  auto filler = [](auto i, auto) { return i % 3 ? true : false; };

  eve::logical<EVE_TYPE> simd(filler);
  eve::logical<EVE_TYPE> ref;

  for(std::ptrdiff_t i = 0; i < simd.size(); ++i)
    ref.set(i, filler(i, simd.size()));

  TTS_EQUAL(simd, ref);
}
