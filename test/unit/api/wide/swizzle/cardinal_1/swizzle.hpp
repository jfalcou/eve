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
#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

template<typename N, typename Env> void test_swizzle(Env& runtime)
{
  using out_t  = eve::wide<EVE_TYPE, eve::fixed<1>>;
  using lout_t = eve::logical<eve::wide<EVE_TYPE, eve::fixed<1>>>;

  eve::wide<EVE_TYPE, N>                        simd([](int i, int) { return 1+i; });
  eve::logical<eve::wide<EVE_TYPE, N>>  logical_simd([](int i, int) { return (1+i)%3 == 0; });

  TTS_EQUAL( simd[ eve::pattern<-1> ]        ,  out_t(0)    );
  TTS_EQUAL( logical_simd[ eve::pattern<-1> ], lout_t(false));

  eve::detail::apply<N::value>
  ( [&](auto const&... n)
    {
      auto t = [&]<typename V>(V const&)
      {
        TTS_EQUAL( simd[ eve::pattern<V::value> ]        ,  out_t(V::value+1) );
        TTS_EQUAL( logical_simd[ eve::pattern<V::value> ], lout_t( (V::value+1)%3 == 0 ) );
      };

      (t(n),...);
    }
  );
}

TTS_CASE_TPL("Check swizzle for wide with 1-lane patterns"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  test_swizzle<T>(runtime);
}
