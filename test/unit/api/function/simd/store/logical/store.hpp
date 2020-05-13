//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef STORE_HPP
#define STORE_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::as_aligned;
using eve::fixed;

TTS_CASE_TPL("Check store behavior to unaligned logical pointer",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  auto filler = [](auto i, auto) { return i % 3 == 0; };

  logical<wide<EVE_TYPE, T>>                  simd(filler);
  std::array<logical<EVE_TYPE>, 3 * T::value> target;

  eve::store(simd, &target[ 0 ]);
  eve::store(simd, &target[ T::value ]);
  eve::store(simd, &target[ 2 * T::value ]);

  logical<wide<EVE_TYPE, T>> st0(&target[ 0 ]);
  logical<wide<EVE_TYPE, T>> st1(&target[ T::value ]);
  logical<wide<EVE_TYPE, T>> st2(&target[ 2 * T::value ]);

  TTS_EQUAL(simd,st0);
  TTS_EQUAL(simd,st1);
  TTS_EQUAL(simd,st2);
}

TTS_CASE_TPL("Check store behavior to aligned pointer of logical",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  auto filler = [](auto i, auto) { return i % 3 == 0; };

  constexpr auto algt = logical<wide<EVE_TYPE, T>>::alignment();

  logical<wide<EVE_TYPE, T>>                                simd(filler);
  alignas(algt) std::array<logical<EVE_TYPE>, 3 * T::value> target;

  eve::store(simd, as_aligned<algt>(&target[ 0 ]));
  eve::store(simd, as_aligned<algt>(&target[ T::value ]));
  eve::store(simd, as_aligned<algt>(&target[ 2 * T::value ]));

  logical<wide<EVE_TYPE, T>> st0(&target[ 0 ]);
  logical<wide<EVE_TYPE, T>> st1(&target[ T::value ]);
  logical<wide<EVE_TYPE, T>> st2(&target[ 2 * T::value ]);

  TTS_EQUAL(simd,st0);
  TTS_EQUAL(simd,st1);
  TTS_EQUAL(simd,st2);
}

#endif
