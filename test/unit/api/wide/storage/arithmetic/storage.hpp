//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <tts/tests/relation.hpp>
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
