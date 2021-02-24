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
  eve::logical<T>  simd([](auto i, auto) { return i%2 == 0; });
  eve::logical<T>  ref;

  // Access via const storage
  auto const& st  = simd.storage();

  // Modification via mutable storage
  ref.storage() = st;

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check front/back access for wide", EVE_TYPE)
{
  eve::logical<T> simd([](auto i, auto) { return i%2 == 0; });

  TTS_EQUAL(simd.front(), true );
  TTS_EQUAL(simd.back() , (EVE_CARDINAL == 1));
}
