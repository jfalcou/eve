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

TTS_CASE("Check storage access for wide")
{
  eve::logical<EVE_TYPE>  simd([](auto i, auto) { return 1+i; });
  eve::logical<EVE_TYPE>  ref;

  // Access via const storage
  auto const& st  = simd.storage();

  // Modification via mutable storage
  ref.storage() = st;

  TTS_EQUAL(simd, ref);
}
