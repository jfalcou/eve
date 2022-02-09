//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of dist"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::dist(T(), T()  ) , T);
  TTS_EXPR_IS( eve::dist(T(), v_t()) , T);
  TTS_EXPR_IS( eve::dist(v_t(), T()) , T);
  TTS_EXPR_IS( eve::dist(T(),int()) , T);
  TTS_EXPR_IS( eve::dist(int(), T()) , T);
  TTS_EXPR_IS( eve::dist(v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::saturated(eve::dist)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::dist)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::dist)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::dist)(T(),int()) , T);
  TTS_EXPR_IS( eve::saturated(eve::dist)(int(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::dist)(v_t(), v_t()) , v_t);
};

//==================================================================================================
//== dist tests
//==================================================================================================
EVE_TEST( "Check behavior of dist(wide)"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1)
{
  using eve::dist;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( dist(a0, a1), map([](auto e, auto f) -> v_t { return std::max(e, f)-std::min(f, e); }, a0, a1), 2);
  TTS_ULP_EQUAL( eve::saturated(dist)(a0, a1), map([](auto e, auto f) -> v_t { v_t d = eve::max(e, f)-eve::min(f, e);
                                                     if constexpr( eve::unsigned_value<v_t>) return d;
                                                     else return d < 0 ? eve::valmax(eve::as(e)): d; }
                                                  , a0, a1), 2);
};

//==================================================================================================
//== diff(dist) tests
//==================================================================================================
EVE_TEST( "Check behavior of diff(dist)(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              )
            )
<typename T>( T const& a0, T const& a1)
{
  using eve::dist;
  using eve::as;
  using v_t =  eve::element_type_t<T>;
  TTS_EQUAL( eve::diff_1st(dist)(a0, a1), map([](auto x, auto y)  -> v_t{ return eve::sign(x-y); }, a0, a1));
  TTS_EQUAL( eve::diff_2nd(dist)(a0, a1), map([](auto x, auto y)  -> v_t{ return eve::sign(y-x); }, a0, a1));
};
