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
#include <eve/function/asecd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/diff/asecd.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asecd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asecd(T())  , T);
  TTS_EXPR_IS( eve::asecd(v_t()), v_t);
};

//==================================================================================================
// asecd  tests
//==================================================================================================
EVE_TEST( "Check behavior of asecd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(1.0, 100.0)
                             , eve::test::randoms(1.0, eve::valmax)
                             , eve::test::randoms(eve::valmin, -1.0)
                             , eve::test::randoms(-100.0, -1.0))
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sasecd = [](auto e) -> v_t { return eve::radindeg(std::acos(1/e)); };
  auto dasecd = [](auto e) -> v_t { return eve::radindeg(v_t(1)/(std::abs(e)*std::sqrt(e*e-1))); };
  TTS_ULP_EQUAL(eve::asecd(a0)           , map(sasecd, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecd)(a0), map(dasecd, a0), 2);
  TTS_ULP_EQUAL(eve::asecd(a1)           , map(sasecd, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecd)(a1), map(dasecd, a1), 2);
  TTS_ULP_EQUAL(eve::asecd(a2)           , map(sasecd, a2), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecd)(a2), map(dasecd, a2), 2);
  TTS_ULP_EQUAL(eve::asecd(a3)           , map(sasecd, a3), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecd)(a3), map(dasecd, a3), 2);

};
