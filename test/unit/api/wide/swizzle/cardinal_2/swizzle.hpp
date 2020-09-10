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

TTS_CASE("Check swizzle for wide with 2-lanes patterns over 1-lane register" )
{
  using out_t  = eve::wide<EVE_TYPE, eve::fixed<2>>;
  using lout_t = eve::logical<eve::wide<EVE_TYPE, eve::fixed<2>>>;

  eve::wide<EVE_TYPE, eve::fixed<1>>                        simd(42);
  eve::logical<eve::wide<EVE_TYPE, eve::fixed<1>>>  logical_simd(true);

  TTS_EQUAL( (simd[ eve::pattern<-1,-1> ]), out_t(0 , 0) );
  TTS_EQUAL( (simd[ eve::pattern<-1, 0> ]), out_t(0 ,42) );
  TTS_EQUAL( (simd[ eve::pattern< 0, 0> ]), out_t(42,42) );
  TTS_EQUAL( (simd[ eve::pattern< 0,-1> ]), out_t(42, 0) );

  TTS_EQUAL( (logical_simd[ eve::pattern<-1,-1> ]), lout_t(false,false) );
  TTS_EQUAL( (logical_simd[ eve::pattern<-1, 0> ]), lout_t(false,true ) );
  TTS_EQUAL( (logical_simd[ eve::pattern< 0, 0> ]), lout_t(true ,true ) );
  TTS_EQUAL( (logical_simd[ eve::pattern< 0,-1> ]), lout_t(true ,false) );
}

template<typename Env, typename Wide> void test_N_2(Env& runtime, Wide base)
{
  using out_t  = eve::as_wide_t<Wide, eve::fixed<2>>;
  using t_t    = eve::element_type_t<Wide>;

  auto ref = [&](int p0, int p1)  { return out_t{ p0==-1 ? t_t(0) : base[p0]
                                                , p1==-1 ? t_t(0) : base[p1]
                                                };
                                  };


  auto permute_1st = [&]<typename V, int... N>( std::integer_sequence<int,N...> const&, V const& )
  {
    auto test = [&]<typename M>(M const&)
                {
                  runtime.output()  << ".. with pattern<"
                                    << ::tts::detail::magenta << V::value << ::tts::detail::reset
                                    << ", "
                                    << ::tts::detail::magenta << M::value << ::tts::detail::reset
                                    << "> " << std::endl;
                  TTS_EQUAL( (base[ eve::pattern<V::value,M::value> ]), (ref(V::value, M::value)) );
                };
    (test(std::integral_constant<int,N-1>{}),...);
  };

  auto permute_2nd = [&]<int... N>( std::integer_sequence<int,N...> const& )
  {
    (permute_1st( std::make_integer_sequence<int,1+eve::cardinal_v<Wide>>{}
                , std::integral_constant<int,N-1>{}
                ), ...
    );
  };

  permute_2nd(std::make_integer_sequence<int,1+eve::cardinal_v<Wide>>{});


  TTS_EQUAL( (base[ eve::pattern<Wide::static_size-1,Wide::static_size-2> ]), (ref(Wide::static_size-1,Wide::static_size-2)) );

  if constexpr( Wide::static_size > 2 )
    TTS_EQUAL( (base[ eve::pattern<Wide::static_size/2-1,Wide::static_size/2-2> ]), (ref(Wide::static_size/2-1,Wide::static_size/2-2)) );
}

/*
TTS_CASE_TPL("Check swizzle for arithmetic wide with 2-lanes patterns over k-lanes register"
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            )
{
  eve::wide<EVE_TYPE, T>  simd([](int i,int) { return 1+i; });
  test_N_2(runtime, simd);
}*/

// TTS_CASE_TPL("Check swizzle for logical wide with 2-lanes patterns over k-lanes register"
//             , eve::fixed<2>
//             , eve::fixed<4>
//             // , eve::fixed<8>
//             // , eve::fixed<16>
//             )
// {
//   eve::logical<eve::wide<EVE_TYPE, T>>  simd(true);
//   test_N_2(runtime, simd);
// }
