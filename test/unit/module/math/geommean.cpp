//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of geommean"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::geommean(T(), T()  ) , T);
  TTS_EXPR_IS( eve::geommean(T(), v_t()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), T()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), v_t()) , v_t);

  //multi
  TTS_EXPR_IS( eve::geommean(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::geommean(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::geommean(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::geommean(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
//== geommean tests
//==================================================================================================
EVE_TEST( "Check behavior of geommean(wide)"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(-100, 100)
                                  , eve::test::randoms(-100, 100)
                                  , eve::test::randoms(-100, 100)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::geommean;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( geommean(a0, a1), map([](auto e, auto f) -> v_t { return (eve::sign(e)*eve::sign(f) >= 0) ?
                                           std::sqrt(e*f) :eve::nan(eve::as<v_t>()); }, a0, a1), 2);
  TTS_ULP_EQUAL( geommean(a0, a1, a2), map([](auto e, auto f,  auto g) { return std::cbrt(e*f*g); }, a0, a1, a2), 3);
};

//==================================================================================================
//== diff(geommean) tests
//==================================================================================================
EVE_TEST( "Check behavior of diff(geommean)(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              )
        )
<typename T>( T const& a0, T const& a1, T const& a2 )
{
  using eve::geommean;
  using eve::diff;
  using eve::as;
  using v_t =  eve::element_type_t<T>;
  TTS_ULP_EQUAL( eve::diff_1st(geommean)(a0, a2), map([](auto e, auto f) { return (eve::sign(e)*eve::sign(f) >= 0) ? std::sqrt(eve::abs(f))*std::sqrt(eve::abs(e))/e/2 :eve::nan(eve::as<v_t>()); }, a0, a2), 2);
  TTS_ULP_EQUAL( eve::diff_2nd(geommean)(a0, a2), map([](auto e, auto f) { return (eve::sign(e)*eve::sign(f) >= 0) ? std::sqrt(eve::abs(e))*std::sqrt(eve::abs(f))/f/2 :eve::nan(eve::as<v_t>()); }, a0, a2), 2);
  TTS_ULP_EQUAL( eve::diff_1st(geommean)(a0, a1, a2), map([](auto e, auto f, auto g) { return std::cbrt(f*g)/eve::sqr(std::cbrt(e))/3; }, a0, a1, a2), 4);
  TTS_ULP_EQUAL( eve::diff_2nd(geommean)(a0, a1, a2), map([](auto e, auto f, auto g) { return std::cbrt(e*g)/eve::sqr(std::cbrt(f))/3; }, a0, a1, a2), 4);
  TTS_ULP_EQUAL( eve::diff_3rd(geommean)(a0, a1, a2), map([](auto e, auto f, auto g) { return std::cbrt(e*f)/eve::sqr(std::cbrt(g))/3; }, a0, a1, a2), 4);
 };
