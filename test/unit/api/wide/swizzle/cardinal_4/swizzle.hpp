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

template<typename Env, typename Wide>
void test_1_4( Env& runtime, Wide const& base)
{
  using out_t  = eve::as_wide_t<Wide, eve::fixed<4>>;
  using t_t    = eve::element_type_t<Wide>;

  auto ref    = [&](int p0, int p1, int p2, int p3)
                {
                  return out_t{ p0==-1 ? t_t(0) : base[p0]
                              , p1==-1 ? t_t(0) : base[p1]
                              , p2==-1 ? t_t(0) : base[p2]
                              , p3==-1 ? t_t(0) : base[p3]
                              };
                };

  TTS_EQUAL( (base[ eve::pattern<-1,-1,-1,-1> ]) , (ref(-1,-1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1,-1, 0> ]) , (ref(-1,-1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 0,-1> ]) , (ref(-1,-1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 0, 0> ]) , (ref(-1,-1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0,-1,-1> ]) , (ref(-1, 0,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0,-1, 0> ]) , (ref(-1, 0,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 0,-1> ]) , (ref(-1, 0, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 0, 0> ]) , (ref(-1, 0, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1,-1,-1> ]) , (ref( 0,-1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1,-1, 0> ]) , (ref( 0,-1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 0,-1> ]) , (ref( 0,-1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 0, 0> ]) , (ref( 0,-1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0,-1,-1> ]) , (ref( 0, 0,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0,-1, 0> ]) , (ref( 0, 0,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 0,-1> ]) , (ref( 0, 0, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 0, 0> ]) , (ref( 0, 0, 0, 0)) );
}

TTS_CASE("Check swizzle for arithmetic wide with 4-lanes patterns over 1-lane register" )
{
  eve::wide<EVE_TYPE, eve::fixed<1>>  simd(42);
  test_1_4(runtime, simd );
}

TTS_CASE("Check swizzle for logical wide with 4-lanes patterns over 1-lane register" )
{
  eve::logical<eve::wide<EVE_TYPE, eve::fixed<1>>>  simd(true);
  test_1_4(runtime, simd );
}


template<typename Env, typename Wide>
void test_2_4( Env& runtime, Wide const& base)
{
  using out_t  = eve::as_wide_t<Wide, eve::fixed<4>>;
  using t_t    = eve::element_type_t<Wide>;

  auto ref    = [&](int p0, int p1, int p2, int p3)
                {
                  return out_t{ p0==-1 ? t_t(0) : base[p0]
                              , p1==-1 ? t_t(0) : base[p1]
                              , p2==-1 ? t_t(0) : base[p2]
                              , p3==-1 ? t_t(0) : base[p3]
                              };
                };

  TTS_EQUAL( (base[ eve::pattern<-1,-1,-1,-1> ]), (ref(-1,-1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1,-1, 0> ]), (ref(-1,-1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1,-1, 1> ]), (ref(-1,-1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 0,-1> ]), (ref(-1,-1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 0, 0> ]), (ref(-1,-1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 0, 1> ]), (ref(-1,-1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 1,-1> ]), (ref(-1,-1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 1, 0> ]), (ref(-1,-1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1,-1, 1, 1> ]), (ref(-1,-1, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0,-1,-1> ]), (ref(-1, 0,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0,-1, 0> ]), (ref(-1, 0,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0,-1, 1> ]), (ref(-1, 0,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 0,-1> ]), (ref(-1, 0, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 0, 0> ]), (ref(-1, 0, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 0, 1> ]), (ref(-1, 0, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 1,-1> ]), (ref(-1, 0, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 1, 0> ]), (ref(-1, 0, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 0, 1, 1> ]), (ref(-1, 0, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1,-1,-1> ]), (ref(-1, 1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1,-1, 0> ]), (ref(-1, 1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1,-1, 1> ]), (ref(-1, 1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 0,-1> ]), (ref(-1, 1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 0, 0> ]), (ref(-1, 1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 0, 1> ]), (ref(-1, 1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 1,-1> ]), (ref(-1, 1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 1, 0> ]), (ref(-1, 1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern<-1, 1, 1, 1> ]), (ref(-1, 1, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1,-1,-1> ]), (ref( 0,-1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1,-1, 0> ]), (ref( 0,-1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1,-1, 1> ]), (ref( 0,-1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 0,-1> ]), (ref( 0,-1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 0, 0> ]), (ref( 0,-1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 0, 1> ]), (ref( 0,-1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 1,-1> ]), (ref( 0,-1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 1, 0> ]), (ref( 0,-1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0,-1, 1, 1> ]), (ref( 0,-1, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0,-1,-1> ]), (ref( 0, 0,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0,-1, 0> ]), (ref( 0, 0,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0,-1, 1> ]), (ref( 0, 0,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 0,-1> ]), (ref( 0, 0, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 0, 0> ]), (ref( 0, 0, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 0, 1> ]), (ref( 0, 0, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 1,-1> ]), (ref( 0, 0, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 1, 0> ]), (ref( 0, 0, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 0, 1, 1> ]), (ref( 0, 0, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1,-1,-1> ]), (ref( 0, 1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1,-1, 0> ]), (ref( 0, 1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1,-1, 1> ]), (ref( 0, 1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 0,-1> ]), (ref( 0, 1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 0, 0> ]), (ref( 0, 1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 0, 1> ]), (ref( 0, 1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 1,-1> ]), (ref( 0, 1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 1, 0> ]), (ref( 0, 1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 0, 1, 1, 1> ]), (ref( 0, 1, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1,-1,-1> ]), (ref( 1,-1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1,-1, 0> ]), (ref( 1,-1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1,-1, 1> ]), (ref( 1,-1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 0,-1> ]), (ref( 1,-1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 0, 0> ]), (ref( 1,-1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 0, 1> ]), (ref( 1,-1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 1,-1> ]), (ref( 1,-1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 1, 0> ]), (ref( 1,-1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1,-1, 1, 1> ]), (ref( 1,-1, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0,-1,-1> ]), (ref( 1, 0,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0,-1, 0> ]), (ref( 1, 0,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0,-1, 1> ]), (ref( 1, 0,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 0,-1> ]), (ref( 1, 0, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 0, 0> ]), (ref( 1, 0, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 0, 1> ]), (ref( 1, 0, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 1,-1> ]), (ref( 1, 0, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 1, 0> ]), (ref( 1, 0, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 0, 1, 1> ]), (ref( 1, 0, 1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1,-1,-1> ]), (ref( 1, 1,-1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1,-1, 0> ]), (ref( 1, 1,-1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1,-1, 1> ]), (ref( 1, 1,-1, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 0,-1> ]), (ref( 1, 1, 0,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 0, 0> ]), (ref( 1, 1, 0, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 0, 1> ]), (ref( 1, 1, 0, 1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 1,-1> ]), (ref( 1, 1, 1,-1)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 1, 0> ]), (ref( 1, 1, 1, 0)) );
  TTS_EQUAL( (base[ eve::pattern< 1, 1, 1, 1> ]), (ref( 1, 1, 1, 1)) );
}

TTS_CASE("Check swizzle for arithmetic wide with 4-lanes patterns over 2-lanes register" )
{
  eve::wide<EVE_TYPE, eve::fixed<2>>  simd(42,69);
  test_2_4(runtime, simd );
}

TTS_CASE("Check swizzle for logical wide with 4-lanes patterns over 2-lanes register" )
{
  eve::logical<eve::wide<EVE_TYPE, eve::fixed<2>>>  simd(true);
  test_2_4(runtime, simd );
}

// TTS_CASE("Check swizzle for arithmetic wide with 4-lanes patterns over 4-lanes register" )
// {
//   eve::wide<EVE_TYPE, eve::fixed<4>>  simd(42,69,13,37);
//   test_N_4(runtime, simd );
// }

// TTS_CASE("Check swizzle for logical wide with 4-lanes patterns over 4-lanes register" )
// {
//   eve::logical<eve::wide<EVE_TYPE, eve::fixed<4>>>  simd(true);
//   test_N_4(runtime, simd );
// }

// TTS_CASE_TPL("Check swizzle for arithmetic wide with 4-lanes patterns over k-lanes register"
//             , eve::fixed<4>
//             , eve::fixed<8>
//             , eve::fixed<16>
//             )
// {
//   eve::wide<EVE_TYPE, T>  simd([](int i,int) { return 1+i; });
//   test_N_2(runtime, simd);
// }

// TTS_CASE_TPL("Check swizzle for logical wide with 4-lanes patterns over k-lanes register"
//             , eve::fixed<4>
//             , eve::fixed<8>
//             , eve::fixed<16>
//             )
// {
//   eve::logical<eve::wide<EVE_TYPE, T>>  simd(true);
//   test_N_2(runtime, simd);
// }
