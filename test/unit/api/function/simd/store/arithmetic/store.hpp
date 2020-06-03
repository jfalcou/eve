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

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <tts/tests/sequence.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <eve/wide.hpp>

using eve::as_aligned;
using eve::fixed;
using eve::wide;

template<int N> alignas(wide<EVE_TYPE>::alignment()) std::array<EVE_TYPE, 3 * N> target;

TTS_CASE_TPL("Check store behavior to unaligned arithmetic pointer",
              fixed<1>,
              fixed<2>,
              fixed<4>,
              fixed<8>,
              fixed<16>,
              fixed<32>,
              fixed<64>)
{
  auto filler = [](auto i, auto) { return 1 + i * 3; };

  wide<EVE_TYPE, T>                   simd(filler);
  std::array<EVE_TYPE, 3 * T::value>  ref;

  for(int i = 0; i < T::value; ++i)
  {
    ref[ i             ] =  1 + i * 3;
    ref[ i + T::value  ] =  1 + i * 3;
    ref[ i + 2*T::value] =  1 + i * 3;
  }

  eve::store(simd, &target<T::value>[ 0 ]);
  eve::store(simd, &target<T::value>[ T::value ]);
  eve::store(simd, &target<T::value>[ 2 * T::value ]);

  TTS_ALL_EQUAL(target<T::value>, ref);
}

TTS_CASE_TPL("Check store behavior to aligned pointer of arithmetic",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  auto filler = [](auto i, auto) { return i +1; };

  constexpr auto algt = wide<EVE_TYPE, T>::alignment();

  wide<EVE_TYPE, T>                   simd(filler);
  std::array<EVE_TYPE, 3 * T::value>  ref;

  for(int i = 0; i < T::value; ++i)
  {
    ref[ i             ] = i+1;
    ref[ i + T::value  ] = i+1;
    ref[ i + 2*T::value] = i+1;
  }

  eve::store(simd, as_aligned<algt>(&target<T::value>[ 0 ]));
  eve::store(simd, as_aligned<algt>(&target<T::value>[ T::value ]));
  eve::store(simd, as_aligned<algt>(&target<T::value>[ 2 * T::value ]));

  TTS_ALL_EQUAL(target<T::value>, ref);
}
