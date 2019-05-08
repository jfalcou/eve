//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#include <algorithm>

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

  logical<wide<Type,T>>                  simd(filler);
  std::array<logical<Type>, 3 * T::value> ref;
  std::array<logical<Type>, 3 * T::value> target;

  for(std::size_t i = 0; i < T::value; ++i)
  {
    auto v   = filler(i, T::value);
    ref[ i ] = ref[ i + T::value ] = ref[ i + 2 * T::value ] = static_cast<Type>(v);
  }

  eve::store(simd, &target[ 0 ]);
  eve::store(simd, &target[ T::value ]);
  eve::store(simd, &target[ 2 * T::value ]);

  TTS_EXPECT(std::equal(target.begin(), target.end(), ref.begin()));
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

  constexpr auto algt = logical<wide<Type,T>>::alignment();

  logical<wide<Type,T>>                                simd(filler);
  alignas(algt) std::array<logical<Type>, 3 * T::value> ref;
  alignas(algt) std::array<logical<Type>, 3 * T::value> target;

  for(std::size_t i = 0; i < T::value; ++i)
  {
    auto v   = filler(i, T::value);
    ref[ i ] = ref[ i + T::value ] = ref[ i + 2 * T::value ] = static_cast<Type>(v);
  }

  eve::store(simd, as_aligned<algt>(&target[ 0 ]));
  eve::store(simd, as_aligned<algt>(&target[ T::value ]));
  eve::store(simd, as_aligned<algt>(&target[ 2 * T::value ]));

  TTS_EXPECT(std::equal(target.begin(), target.end(), ref.begin()));
}

#endif
