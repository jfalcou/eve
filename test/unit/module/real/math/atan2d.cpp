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
#include <eve/function/radindeg.hpp>
#include <eve/function/diff/atan2d.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of atan2d"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atan2d(T(), T())  , T);
  TTS_EXPR_IS( eve::atan2d(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::atan2d(T(), v_t()), T);
  TTS_EXPR_IS( eve::atan2d(v_t(), T()), T);
};

//==================================================================================================
// atan2d  tests
//==================================================================================================
EVE_TEST( "Check behavior of atan2d on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(-1.0, 1.0)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atan2d(a0, a1)      , map([](auto e, auto f) -> v_t { return eve::radindeg(std::atan2(e, f)); }, a0, a1), 2);
  TTS_ULP_EQUAL(eve::atan2d(a2, a3)      , map([](auto e, auto f) -> v_t { return eve::radindeg(std::atan2(e, f)); }, a2, a3), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::atan2d)(a0, a1), map([](auto e, auto f) -> v_t { return  eve::radindeg(f/(e*e+f*f)); }, a0, a1), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::atan2d)(a2, a3), map([](auto e, auto f) -> v_t { return  eve::radindeg(f/(e*e+f*f)); }, a2, a3), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::atan2d)(a0, a1), map([](auto e, auto f) -> v_t { return  eve::radindeg(e/(e*e+f*f)); }, a0, a1), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::atan2d)(a2, a3), map([](auto e, auto f) -> v_t { return  eve::radindeg(e/(e*e+f*f)); }, a2, a3), 2);
};
