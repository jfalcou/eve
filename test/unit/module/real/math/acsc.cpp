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
#include <eve/function/acsc.hpp>
#include <eve/function/diff/acsc.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acsc"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acsc(T())  , T);
  TTS_EXPR_IS( eve::acsc(v_t()), v_t);
};

//==================================================================================================
// acsc  tests
//==================================================================================================
EVE_TEST( "Check behavior of acsc on wide"
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

  auto sacsc = [](auto e) -> v_t { return std::asin(1/e); };
  auto dacsc = [](auto e) -> v_t { return -v_t(1)/(std::abs(e)*std::sqrt(e*e-1)); };
  TTS_ULP_EQUAL(eve::acsc(a0)           , map(sacsc, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsc)(a0), map(dacsc, a0), 2);
  TTS_ULP_EQUAL(eve::acsc(a1)           , map(sacsc, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsc)(a1), map(dacsc, a1), 2);
  TTS_ULP_EQUAL(eve::acsc(a2)           , map(sacsc, a2), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsc)(a2), map(dacsc, a2), 2);
  TTS_ULP_EQUAL(eve::acsc(a3)           , map(sacsc, a3), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsc)(a3), map(dacsc, a3), 2);

};
