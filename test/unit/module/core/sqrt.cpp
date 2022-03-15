//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sqrt"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sqrt(T())  , T);
  TTS_EXPR_IS( eve::sqrt(v_t()), v_t);
  TTS_EXPR_IS( eve::sqrt[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::sqrt[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::sqrt[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::sqrt[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::sqrt[bool()](T())  , T);
  TTS_EXPR_IS( eve::sqrt[bool()](v_t()), v_t);
  TTS_EXPR_IS( eve::diff(eve::sqrt)(T())  , T);
  TTS_EXPR_IS( eve::diff(eve::sqrt)(v_t()), v_t);
};

//==================================================================================================
// sqrt simd tests
//==================================================================================================
EVE_TEST( "Check behavior of sqrt(wide) and diff on  floating types"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
            )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using eve::diff;
  using eve::sqr;
  using eve::rec;
  TTS_ULP_EQUAL( eve::sqrt(a0), map([&](auto e) { return std::sqrt(e); }, a0), 2);
  TTS_ULP_EQUAL( diff(eve::sqrt)(a0), map([&](auto e) { return rec(std::sqrt(e)*2); }, a0), 2.5);
};

//==================================================================================================
// sqrt[cond](simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of sqrt[cond](wide) on  floating types"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(0.0, eve::valmax))
            )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  auto val = eve::unsigned_value<v_t> ? (eve::valmax(eve::as<v_t>())/2) : 0;
  using eve::detail::map;
  TTS_ULP_EQUAL( eve::sqrt[a0 < val](a0), map([&](auto e) { return (e < val)? std::sqrt(e) : e; }, a0), 2);
};
