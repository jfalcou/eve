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

TTS_CASE_TPL("Check slicing for arithmetic wide", EVE_TYPE)
{
  if constexpr( EVE_CARDINAL > 1 )
  {
    using eve::wide;

    using split_t = typename eve::cardinal_t<T>::split_type;
    T                         simd    ([](auto i, auto) { return 1 + i; });
    wide<EVE_VALUE, split_t>  ref_low ([](auto i, auto) { return 1 + i; });
    wide<EVE_VALUE, split_t>  ref_high([](auto i, auto) { return EVE_CARDINAL / 2 + 1 + i; });

    auto [ low, high ] = simd.slice();

    TTS_EQUAL(low, ref_low);
    TTS_EQUAL(simd.slice(eve::lower_), ref_low);
    TTS_EQUAL(high, ref_high);
    TTS_EQUAL(simd.slice(eve::upper_), ref_high);
  }
  else
  {
    TTS_PASS("Small type don't need to be sliced");
  }
}
