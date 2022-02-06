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
EVE_TEST_TYPES( "Check return types of atand"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atand(T())  , T);
  TTS_EXPR_IS( eve::atand(v_t()), v_t);
};

//==================================================================================================
// atand  tests
//==================================================================================================
EVE_TEST( "Check behavior of atand on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atand(a0)      , map([](auto e) -> v_t { return eve::radindeg(std::atan(e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::atand(a1)      , map([](auto e) -> v_t { return eve::radindeg(std::atan(e)); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::atand)(a0), map([](auto e) -> v_t { return  eve::radindeg(v_t(1)/(e*e+1)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::atand)(a1), map([](auto e) -> v_t { return  eve::radindeg(v_t(1)/(e*e+1)); }, a1), 2);
};
