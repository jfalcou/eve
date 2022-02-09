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
#include <eve/module/core/constant/sqrtvalmax.hpp>
#include <eve/function/sqr_abs.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/diff/sqr_abs.hpp>
#include <eve/logical.hpp>
#include <cmath>


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::sqr_abs", eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::sqr_abs;

  TTS_EXPR_IS( sqr_abs(T())                      , T );
  TTS_EXPR_IS( sqr_abs(v_t())                      , v_t );
  TTS_EXPR_IS( eve::diff(eve::sqr_abs)(T()) , T );
  TTS_EXPR_IS( eve::diff(eve::sqr_abs)(v_t()) , v_t );
};



//==================================================================================================
// Tests for eve::sqr_abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::sqr_abs(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::sqr_abs;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(sqr_abs(a0)      , map([](auto e) -> v_t { return e*e; }, a0) );
  TTS_EQUAL(eve::diff(sqr_abs)(a0), 2*a0);
};
