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
#include <eve/wide.hpp>

TTS_CASE_TPL("Check storage access for wide", EVE_TYPE)
{
  eve::logical<T>  simd([](auto i, auto) { return 1+i; });
  eve::logical<T>  ref;

  // Access via const storage
  auto const& st  = simd.storage();

  // Modification via mutable storage
  ref.storage() = st;

  TTS_EQUAL(simd, ref);
}
