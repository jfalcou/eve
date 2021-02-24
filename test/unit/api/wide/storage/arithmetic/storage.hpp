//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/wide.hpp>

TTS_CASE_TPL("Check storage access for wide", EVE_TYPE)
{
  T  simd([](auto i, auto) { return 1+i; });
  T  ref;

  // Access via const storage
  auto const& st  = simd.storage();

  // Modification via mutable storage
  ref.storage() = st;

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check begin/end access for wide", EVE_TYPE)
{
  T  simd([](auto i, auto) { return 1+i; });
  T  ref;

  std::copy( simd.begin(), simd.end(), ref.begin() );

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check front/back access for wide", EVE_TYPE)
{
  T  simd([](auto i, auto) { return 1+i; });

  TTS_EQUAL(simd.front(), EVE_VALUE(1));
  TTS_EQUAL(simd.back() , EVE_VALUE(EVE_CARDINAL));
}
