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
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acosh"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acosh(T())  , T);
  TTS_EXPR_IS( eve::acosh(v_t()), v_t);
};

//==================================================================================================
// acosh  tests
//==================================================================================================
EVE_TEST( "Check behavior of acosh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(1.0, eve::valmax)
                             , eve::test::randoms(1.0, 100.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acosh(a0)      , map([](auto e) -> v_t { return std::acosh(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::acosh(a1)      , map([](auto e) -> v_t { return std::acosh(e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acosh)(a0), map([](auto e) -> v_t { return  v_t(1)/std::sqrt(e*e-1); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acosh)(a1), map([](auto e) -> v_t { return  v_t(1)/std::sqrt(e*e-1); }, a1), 2);
};
