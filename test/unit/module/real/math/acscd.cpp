//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/acscd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/diff/acscd.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acscd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acscd(T())  , T);
  TTS_EXPR_IS( eve::acscd(v_t()), v_t);
};

//==================================================================================================
// acscd  tests
//==================================================================================================
EVE_TEST( "Check behavior of acscd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(1.0, 100.0)
                              , eve::test::randoms(1.0, 1e20)
                              , eve::test::randoms(-1e20, -1.0)
                              , eve::test::randoms(-100.0, -1.0)
                              )
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sacscd = [](auto e) -> v_t { return eve::radindeg(std::asin(1/e)); };
  auto dacscd = [](auto e) -> v_t { return eve::radindeg(-v_t(1)/(std::abs(e)*std::sqrt(e*e-1))); };
  TTS_ULP_EQUAL(eve::acscd(a0)           , map(sacscd, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscd)(a0), map(dacscd, a0), 2);
  TTS_ULP_EQUAL(eve::acscd(a1)           , map(sacscd, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscd)(a1), map(dacscd, a1), 2);
  TTS_ULP_EQUAL(eve::acscd(a2)           , map(sacscd, a2), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscd)(a2), map(dacscd, a2), 2);
  TTS_ULP_EQUAL(eve::acscd(a3)           , map(sacscd, a3), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscd)(a3), map(dacscd, a3), 2);

};
