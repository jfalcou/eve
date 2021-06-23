//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/function/sqr_abs.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/diff/sqr_abs.hpp>
#include <eve/function/saturated/sqr_abs.hpp>
#include <eve/logical.hpp>
#include <cmath>


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::sqr_abs", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::sqr_abs;
  using eve::saturated;

  TTS_EXPR_IS( sqr_abs(T())                      , T );
  TTS_EXPR_IS( sqr_abs[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( sqr_abs[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( sqr_abs[bool()](T())              , T );

  TTS_EXPR_IS( saturated(eve::sqr_abs)(T())                      , T );
  TTS_EXPR_IS( saturated(eve::sqr_abs[eve::logical<T>()])(T())   , T );
  TTS_EXPR_IS( saturated(eve::sqr_abs[eve::logical<v_t>()])(T()) , T );
  TTS_EXPR_IS( saturated(eve::sqr_abs[bool()])(T())              , T );

  TTS_EXPR_IS( sqr_abs(v_t())                      , v_t );
  TTS_EXPR_IS( sqr_abs[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( sqr_abs[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( sqr_abs[bool()](v_t())              , v_t );

  TTS_EXPR_IS( saturated(eve::sqr_abs)(v_t())                      , v_t );
  TTS_EXPR_IS( saturated(eve::sqr_abs[eve::logical<T>()])(v_t())   , T );
  TTS_EXPR_IS( saturated(eve::sqr_abs[eve::logical<v_t>()])(v_t()) , v_t );
  TTS_EXPR_IS( saturated(eve::sqr_abs[bool()])(v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::sqr_abs)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::sqr_abs)(v_t()) , v_t );
  }
};



//==================================================================================================
// Tests for eve::sqr_abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::sqr_abs(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using eve::sqr_abs;
  using eve::saturated;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(sqr_abs(a0)      , map([](auto e) -> v_t { return e*e; }, a0) );
  TTS_EQUAL(sqr_abs[mask](a0), eve::if_else(mask,eve::sqr_abs(a0),a0)                    );
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(saturated(sqr_abs)(a0)      , map([](auto e) -> v_t { return saturated(eve::abs)(e) > eve::sqrtvalmax(as(e)) ? eve::valmax(as(e)) : e*e; }, a0) );
    TTS_EQUAL(saturated(sqr_abs[mask])(a0), eve::if_else(mask,saturated(sqr_abs)(a0),a0)                    );
  }
  else if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL(eve::diff(sqr_abs)(a0), 2*a0);
  }
};
