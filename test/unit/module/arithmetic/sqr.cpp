//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/arithmetic/constant/sqrtvalmax.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/diff/sqr.hpp>
#include <eve/function/saturated/sqr.hpp>
#include <eve/logical.hpp>
#include <cmath>


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::sqr", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::sqr;
  using eve::saturated;

  TTS_EXPR_IS( sqr(T())                      , T );
  TTS_EXPR_IS( sqr[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( sqr[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( sqr[bool()](T())              , T );

  TTS_EXPR_IS( saturated(eve::sqr)(T())                      , T );
  TTS_EXPR_IS( saturated(eve::sqr[eve::logical<T>()])(T())   , T );
  TTS_EXPR_IS( saturated(eve::sqr[eve::logical<v_t>()])(T()) , T );
  TTS_EXPR_IS( saturated(eve::sqr[bool()])(T())              , T );

  TTS_EXPR_IS( sqr(v_t())                      , v_t );
  TTS_EXPR_IS( sqr[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( sqr[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( sqr[bool()](v_t())              , v_t );

  TTS_EXPR_IS( saturated(eve::sqr)(v_t())                      , v_t );
  TTS_EXPR_IS( saturated(eve::sqr[eve::logical<T>()])(v_t())   , T );
  TTS_EXPR_IS( saturated(eve::sqr[eve::logical<v_t>()])(v_t()) , v_t );
  TTS_EXPR_IS( saturated(eve::sqr[bool()])(v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::sqr)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::sqr)(v_t()) , v_t );
  }
};



//==================================================================================================
// Tests for eve::sqr
//==================================================================================================
EVE_TEST( "Check behavior of eve::sqr(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using eve::sqr;
  using eve::saturated;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(sqr(a0)      , map([](auto e) -> v_t { return e*e; }, a0) );
  TTS_EQUAL(sqr[mask](a0), eve::if_else(mask,eve::sqr(a0),a0)                    );
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(saturated(sqr)(a0)      , map([](auto e) -> v_t { return saturated(eve::abs)(e) > eve::sqrtvalmax(as(e)) ? eve::valmax(as(e)) : e*e; }, a0) );
    TTS_EQUAL(saturated(sqr[mask])(a0), eve::if_else(mask,saturated(sqr)(a0),a0)                    );
  }
  else if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL(eve::diff(sqr)(a0), 2*a0);
  }
};
