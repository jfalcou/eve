//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/pattern.hpp>
#include <iostream>

TTS_CASE("Check pattern properties checks")
{
  using eve::na_;

  TTS_CONSTEXPR_EQUAL ( (eve::pattern<0,1,2,3>.size()), 4ull );

  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<na_, 1, 2, 3>.has_zeros()));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0,na_, 2, 3>.has_zeros()));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1,na_, 3>.has_zeros()));
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1, 2,na_>.has_zeros()));
  TTS_CONSTEXPR_EXPECT_NOT( (eve::pattern< 0, 1, 2, 3>.has_zeros()));

  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0,na_, 2,na_>.validate(4)) );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern< 0, 1, 2, 3>.validate(4)) );
  TTS_CONSTEXPR_EXPECT_NOT( (eve::pattern< 0, 1, 2, 4>.validate(4)) );
};

TTS_CASE("Check lambda-pattern properties checks")
{
  using eve::na_;

  constexpr auto f = [](auto i, auto) { return i%2 ? na_ : i/2; };

  TTS_CONSTEXPR_EQUAL ( eve::fix_pattern<4>(f).size(), 4ull   );
  TTS_CONSTEXPR_EXPECT( eve::fix_pattern<4>(f).has_zeros() );
  TTS_CONSTEXPR_EXPECT( eve::fix_pattern<4>(f).validate(4) );

  TTS_CONSTEXPR_EQUAL ( eve::fix_pattern<8>(f).size(), 8ull  );
  TTS_CONSTEXPR_EXPECT( eve::fix_pattern<8>(f).has_zeros());
  TTS_CONSTEXPR_EXPECT( eve::fix_pattern<8>(f).validate(8));
};

TTS_CASE("Check pattern random access behavior")
{
  constexpr auto p = eve::pattern<0,1,2,3>;

  TTS_CONSTEXPR_EQUAL(p(0,4), 0);
  TTS_CONSTEXPR_EQUAL(p(1,4), 1);
  TTS_CONSTEXPR_EQUAL(p(2,4), 2);
  TTS_CONSTEXPR_EQUAL(p(3,4), 3);
};

TTS_CASE("Check lambda-pattern random access behavior")
{
  using eve::na_;

  constexpr auto f = [](auto i, auto) { return i%2 ? na_ : i/2; };

  TTS_CONSTEXPR_EQUAL(eve::fix_pattern<4>(f)(1,4),na_);
  TTS_CONSTEXPR_EQUAL(eve::fix_pattern<4>(f)(0,4), 0);
  TTS_CONSTEXPR_EQUAL(eve::fix_pattern<4>(f)(2,4), 1);
  TTS_CONSTEXPR_EQUAL(eve::fix_pattern<4>(f)(3,4),na_);
};

TTS_CASE("Check pattern comparison operators")
{
  TTS_CONSTEXPR_EQUAL     ( (eve::pattern<0,1,2,3>), (eve::pattern<0,1,2,3>)    );
  TTS_CONSTEXPR_NOT_EQUAL ( (eve::pattern<0,1,2,3>), (eve::pattern<0,2,1,3>)    );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,1,2,3,4,5,6,7>  ).strictly_under(8) );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<0,0,1,1,2,2,3,3>  ).under(3)          );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<4,5,6,7,8,9,10,11>).strictly_over(2)  );
  TTS_CONSTEXPR_EXPECT    ( (eve::pattern<4,5,6,7,8,9,10,11>).over(4)           );
};

TTS_CASE("Check lambda-pattern comparison operators")
{
  constexpr auto s = eve::fix_pattern<8>([](auto i, auto) { return 2*(i/2); });

  TTS_CONSTEXPR_EQUAL     ( s , (eve::pattern<0,0,2,2,4,4,6,6>) );
  TTS_CONSTEXPR_NOT_EQUAL ( s , (eve::pattern<0,2,1,3,5,4,2,1>) );
  TTS_CONSTEXPR_EXPECT    ( s.strictly_under(8) );
  TTS_CONSTEXPR_EXPECT    ( s.under(6) );

  constexpr auto t = eve::fix_pattern<8>([](auto i, auto) { return 2*(i/2)+4; });

  TTS_CONSTEXPR_EXPECT( t.strictly_over(2) );
  TTS_CONSTEXPR_EXPECT( t.over(4) );
};

TTS_CASE("Check pattern_clamp effects")
{
  constexpr auto q = eve::pattern<0,1,2,3,4,5,6,7>;

  TTS_CONSTEXPR_EQUAL ( eve::pattern_clamp<1>(q), (eve::pattern<0>) );
  TTS_CONSTEXPR_EQUAL ( eve::pattern_clamp<2>(q), (eve::pattern<0,1>) );
  TTS_CONSTEXPR_EQUAL ( eve::pattern_clamp<4>(q), (eve::pattern<0,1,2,3>) );
  TTS_CONSTEXPR_EQUAL ( eve::pattern_clamp<8>(q), (eve::pattern<0,1,2,3,4,5,6,7>) );
};

TTS_CASE("Check pattern_view effects")
{
  constexpr auto q = eve::pattern<0,1,2,3,4,5,6,7>;

  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<0,2,8>(q)), (eve::pattern<0,1>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<1,3,8>(q)), (eve::pattern<1,2>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<2,4,8>(q)), (eve::pattern<2,3>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<3,5,8>(q)), (eve::pattern<3,4>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<4,6,8>(q)), (eve::pattern<4,5>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<5,7,8>(q)), (eve::pattern<5,6>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<6,8,8>(q)), (eve::pattern<6,7>) );

  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<1,5,8>(q)), (eve::pattern<1,2,3,4>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<0,4,8>(q)), (eve::pattern<0,1,2,3>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<2,6,8>(q)), (eve::pattern<2,3,4,5>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<3,7,8>(q)), (eve::pattern<3,4,5,6>) );
  TTS_CONSTEXPR_EQUAL ( (eve::pattern_view<4,8,8>(q)), (eve::pattern<4,5,6,7>) );
};
