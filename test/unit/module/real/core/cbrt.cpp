//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/diff/cbrt.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cbrt"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cbrt(T())  , T);
  TTS_EXPR_IS( eve::cbrt(v_t()), v_t);
  TTS_EXPR_IS( eve::cbrt[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::cbrt[bool()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[bool()](v_t()), v_t);
  TTS_EXPR_IS( eve::diff(eve::cbrt)(T())  , T);
  TTS_EXPR_IS( eve::diff(eve::cbrt)(v_t()), v_t);
};

//==================================================================================================
// cbrt tests
//==================================================================================================
EVE_TEST( "Check behavior of cbrt(wide) and diff on  floating types"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
            )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using eve::diff;
  using eve::sqr;
  using eve::rec;
  TTS_ULP_EQUAL( eve::cbrt(a0), map([&](auto e) { return std::cbrt(e); }, a0), 2);
  TTS_ULP_EQUAL( diff(eve::cbrt)(a0), map([&](auto e) { return rec(sqr(std::cbrt(e))*3); }, a0), 2.5);
};

EVE_TEST( "Check behavior of cbrt(scalar)  and diff on  floating types"
            , eve::test::scalar::ieee_reals
            , eve::test::generate ( eve::test::randoms(-100, 100))
            )
<typename T>(T const& a0 )
{
  for(auto a: a0)
  {
    using eve::diff;
    using eve::sqr;
    using eve::rec;
    TTS_ULP_EQUAL( eve::cbrt(a), std::cbrt(a), 2);
    TTS_ULP_EQUAL( diff(eve::cbrt)(a), rec(sqr(std::cbrt(a))*3), 2);
  }
};
