//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asin"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asin(T())  , T);
  TTS_EXPR_IS( eve::asin(v_t()), v_t);
};

//==================================================================================================
// asin  tests
//==================================================================================================
EVE_TEST( "Check behavior of asin on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1, 1))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asin(a0)      , map([](auto e) -> v_t { return std::asin(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asin)(a0), map([](auto e) -> v_t { return  v_t(1)/std::sqrt(1-e*e); }, a0), 2);
};
