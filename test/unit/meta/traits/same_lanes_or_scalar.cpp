//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/same_lanes.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check same_lanes on simd types" )
{
  using eve::wide;
  using eve::fixed;

  TTS_CONSTEXPR_EXPECT((eve::same_lanes<wide<int>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes<wide<int>,wide<float>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes<wide<int,fixed<8>>,wide<char,fixed<8>>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::same_lanes<wide<int>,wide<char>>));
};

TTS_CASE( "Check same_lanes_or_scalar on scalar types" )
{
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<int>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<int,char>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<int,float>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<double,int,float>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<kumi::tuple<double,int,float>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<kumi::tuple<double,int,float>, int>));
};

TTS_CASE( "Check same_lanes_or_scalar on simd types" )
{
  using eve::wide;
  using eve::fixed;

  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<wide<int>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<wide<int>,wide<float>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<wide<int,fixed<8>>,wide<char,fixed<8>>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::same_lanes_or_scalar<wide<int>,wide<char>>));
};

TTS_CASE( "Check same_lanes_or_scalar on mixed types" )
{
  using eve::wide;
  using eve::fixed;

  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<float,wide<int>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<wide<int>,double,wide<float>>));
  TTS_CONSTEXPR_EXPECT((eve::same_lanes_or_scalar<wide<int,fixed<8>>,short,wide<char,fixed<8>>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::same_lanes_or_scalar<wide<int,fixed<8>>,short,wide<char,fixed<2>>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::same_lanes_or_scalar<double,wide<int>,wide<char>>));
};
