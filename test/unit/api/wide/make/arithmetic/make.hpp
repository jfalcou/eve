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

TTS_CASE_TPL( "Check enumerating constructor for arithmetic wide", EVE_TYPE )
{
  auto filler = [](auto i, auto) { return EVE_VALUE(i + 1); };

  T simd(filler);
  T ref;

  for(std::ptrdiff_t i = 0; i < simd.size(); ++i)
    ref.set(i, filler(i, simd.size()));

  TTS_EQUAL(simd, ref);
}
