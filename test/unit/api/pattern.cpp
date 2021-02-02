//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/pattern.hpp>
#include <iostream>

TTS_CASE("Check pattern properties checks")
{
  TTS_CONSTEXPR_EQUAL ( (eve::pattern<0,1,2,3>.size(4)), 4 );

  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<-1, 1, 2, 3>.has_zeros(4)));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0,-1, 2, 3>.has_zeros(4)));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1,-1, 3>.has_zeros(4)));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1, 2,-1>.has_zeros(4)));
  TTS_CONSTEXPR_EXPECT_NOT( (eve::pattern< 0, 1, 2, 3>.has_zeros(4)));

  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0,-1, 2,-1>.validate(4)) );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1, 2, 3>.validate(4)) );
  TTS_CONSTEXPR_EXPECT_NOT( (eve::pattern< 0, 1, 2, 4>.validate(4)) );
}

TTS_CASE("Check swizzle properties checks")
{
  constexpr auto f = [](auto i, auto) { return i%2 ? -1 : i/2; };

  TTS_CONSTEXPR_EQUAL ( eve::swizzle(f).size(4), 4   );
  TTS_CONSTEXPR_EXPECT( eve::swizzle(f).has_zeros(4) );
  TTS_CONSTEXPR_EXPECT( eve::swizzle(f).validate(4)  );

  TTS_CONSTEXPR_EQUAL ( eve::swizzle<8>(f).size(8), 8   );
  TTS_CONSTEXPR_EXPECT( eve::swizzle<8>(f).has_zeros(8) );
  TTS_CONSTEXPR_EXPECT( eve::swizzle<8>(f).validate(8)  );
}

TTS_CASE("Check pattern random access behavior")
{
  constexpr auto p = eve::pattern<0,1,2,3>;

  TTS_CONSTEXPR_EQUAL(p(0,4), 0);
  TTS_CONSTEXPR_EQUAL(p(1,4), 1);
  TTS_CONSTEXPR_EQUAL(p(2,4), 2);
  TTS_CONSTEXPR_EQUAL(p(3,4), 3);
}

TTS_CASE("Check swizzle random access behavior")
{
  constexpr auto f = [](auto i, auto) { return i%2 ? -1 : i/2; };

  TTS_CONSTEXPR_EQUAL(eve::swizzle(f)(0,4), 0);
  TTS_CONSTEXPR_EQUAL(eve::swizzle(f)(1,4),-1);
  TTS_CONSTEXPR_EQUAL(eve::swizzle(f)(2,4), 1);
  TTS_CONSTEXPR_EQUAL(eve::swizzle(f)(3,4),-1);
}

TTS_CASE("Check pattern similarity")
{
  constexpr auto q = eve::pattern<0,1,2,3,4,5,6,7>;

  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<0,1>)                       );
  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<1,0>)                       );
  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<0,1,2>)                     );
  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<2,1,0>)                     );
  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<0,1,2,3>)                   );
  TTS_CONSTEXPR_EXPECT_NOT( q.is_similar(eve::pattern<1,2,3,0>)                   );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,1>.is_similar(q))                     );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,1,2>.is_similar(q))                   );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,1,2,3>.is_similar(q))                 );
  TTS_CONSTEXPR_EXPECT    ( q.is_similar(eve::pattern<0,1,2,3,4,5,6,7>)           );
  TTS_CONSTEXPR_EXPECT    ( q.is_similar(eve::pattern<0,1,2,3,4,5,6,7,8,9,10,15>) );
}

TTS_CASE("Check swizzle similarity")
{
  constexpr auto f = [](auto i, auto) { return 2*(i/2); };
  constexpr auto s = eve::as_pattern<4>(eve::swizzle(f));

  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<0,1>)       );
  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<1,0>)       );
  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<0,1,2>)     );
  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<2,1,0>)     );
  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<0,1,2,3>)   );
  TTS_CONSTEXPR_EXPECT_NOT( s.is_similar(eve::pattern<1,2,3,0>)   );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0>.is_similar(s))       );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,0>.is_similar(s))     );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,0,2>.is_similar(s))   );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,0,2,2>.is_similar(s)) );
}

TTS_CASE("Check pattern comparison operators")
{
  TTS_CONSTEXPR_EQUAL         ( (eve::pattern<0,1,2,3>)           , (eve::pattern<0,1,2,3>) );
  TTS_CONSTEXPR_NOT_EQUAL     ( (eve::pattern<0,1,2,3>)           , (eve::pattern<0,2,1,3>) );
  TTS_CONSTEXPR_LESS          ( (eve::pattern<0,1,2,3,4,5,6,7>  ) , 8                       );
  TTS_CONSTEXPR_LESS_EQUAL    ( (eve::pattern<0,0,1,1,2,2,3,3>  ) , 3                       );
  TTS_CONSTEXPR_GREATER       ( (eve::pattern<4,5,6,7,8,9,10,11>) , 2                       );
  TTS_CONSTEXPR_GREATER_EQUAL ( (eve::pattern<4,5,6,7,8,9,10,11>) , 4                       );
}

TTS_CASE("Check swizzle comparison operators")
{
  constexpr auto f = [](auto i, auto) { return 2*(i/2); };
  constexpr auto s = eve::as_pattern<8>(eve::swizzle(f));

  TTS_CONSTEXPR_EQUAL         ( s , (eve::pattern<0,0,2,2,4,4,6,6>) );
  TTS_CONSTEXPR_NOT_EQUAL     ( s , (eve::pattern<0,2,1,3,5,4,2,1>) );
  TTS_CONSTEXPR_LESS          ( s , 8 );
  TTS_CONSTEXPR_LESS_EQUAL    ( s , 6 );

  constexpr auto g = [](auto i, auto) { return 2*(i/2)+4; };
  constexpr auto t = eve::as_pattern<8>(eve::swizzle(g));

  TTS_CONSTEXPR_GREATER       ( t, 2 );
  TTS_CONSTEXPR_GREATER_EQUAL ( t, 4 );
}

TTS_CASE("Check pattern_clamp effects")
{
  constexpr auto q = eve::pattern<0,1,2,3,4,5,6,7>;

  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<1>(eve::pattern_clamp<1>(q)), (eve::pattern<0>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<2>(eve::pattern_clamp<2>(q)), (eve::pattern<0,1>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_clamp<4>(q)), (eve::pattern<0,1,2,3>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<8>(eve::pattern_clamp<8>(q)), (eve::pattern<0,1,2,3,4,5,6,7>) );
}

TTS_CASE("Check pattern_view effects")
{
  constexpr auto q = eve::pattern<0,1,2,3,4,5,6,7>;

  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<0,2,8>(q)), (eve::pattern<0,1>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<1,3,8>(q)), (eve::pattern<1,2>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<2,4,8>(q)), (eve::pattern<2,3>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<3,5,8>(q)), (eve::pattern<3,4>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<4,6,8>(q)), (eve::pattern<4,5>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<5,7,8>(q)), (eve::pattern<5,6>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<6,8,8>(q)), (eve::pattern<6,7>) );

  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<0,4,8>(q)), (eve::pattern<0,1,2,3>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<1,5,8>(q)), (eve::pattern<1,2,3,4>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<2,6,8>(q)), (eve::pattern<2,3,4,5>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<3,7,8>(q)), (eve::pattern<3,4,5,6>) );
  TTS_CONSTEXPR_EQUAL ( eve::as_pattern<4>(eve::pattern_view<4,8,8>(q)), (eve::pattern<4,5,6,7>) );
}
