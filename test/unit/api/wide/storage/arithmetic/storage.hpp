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
  T  simd([](auto i, auto) { return 1+i; });
  T  ref;

  // Access via const storage
  auto const& st  = simd.storage();

  // Modification via mutable storage
  ref.storage() = st;

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check begin/end access for wide")
{
  T  simd([](auto i, auto) { return 1+i; });
  T  ref;

  std::copy( simd.begin(), simd.end(), ref.begin() );

  TTS_EQUAL(simd, ref);
}
