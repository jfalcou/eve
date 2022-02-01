//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/saturated/sub.hpp>
#include <eve/function/diff/sub.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sub"
          , eve::test::simd::all_types
          )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::sub(T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub(T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), T()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), v_t()) , v_t);

  //saturated
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(v_t(), T()) , T);


  //multi
  TTS_EXPR_IS( eve::sub(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::sub(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::sub(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::sub(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::sub(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), T(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), v_t(), v_t()) , v_t);

  //diff
  if constexpr(eve::floating_value<T>)
  {
    using eve::diff_1st;
    using eve::diff_2nd;
    TTS_EXPR_IS( diff_1st(eve::sub)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_1st(eve::sub)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_1st(eve::sub)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_1st(eve::sub)(v_t(), v_t()) , v_t);
    TTS_EXPR_IS( diff_2nd(eve::sub)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_2nd(eve::sub)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_2nd(eve::sub)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_2nd(eve::sub)(v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
//==  sub simd tests
//==================================================================================================
EVE_TEST( "Check behavior of sub on wide"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::sub;
  using eve::saturated;
  using eve::detail::map;
  TTS_EQUAL( sub(a0, a2), map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL( saturated(sub)(a0, a2), map([&](auto e, auto f) { return saturated(sub)(e, f); }, a0, a2));
  TTS_EQUAL( sub(a0, a1, a2), map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL( saturated(sub)(a0, a1, a2), map([&](auto e, auto f, auto g) { return saturated(sub)(saturated(sub)(e, f), g); }, a0, a1, a2));
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL( eve::diff_1st(sub)(a0, a2), eve::one(eve::as(a0)));
    TTS_EQUAL( eve::diff_2nd(sub)(a0, a2), eve::mone(eve::as(a0)));
    TTS_EQUAL( eve::diff_3rd(sub)(a0, a1, a2), eve::mone(eve::as(a0)));
  }

};

//==================================================================================================
//==  conditional sub tests on simd
//==================================================================================================
auto mini = [] < typename T > (eve::as<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of sub on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
<typename T>( T const& a0, T const& a1, T const& a2)
{
  using eve::sub;
  using eve::saturated;
  using eve::detail::map;
  TTS_EQUAL( sub[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? sub(e, f) : e ; }, a0, a1, a2));
  TTS_EQUAL( saturated(sub[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? saturated(sub)(e, f): e; }, a0, a1, a2));
};

/// TODO waiting for interface simplifications to add scalar tests
