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
#include <eve/function/asecpi.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/function/diff/asecpi.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asecpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asecpi(T())  , T);
  TTS_EXPR_IS( eve::asecpi(v_t()), v_t);
};

//==================================================================================================
// asecpi  tests
//==================================================================================================
EVE_TEST( "Check behavior of asecpi on wide"
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

  auto sasecpi = [](auto e) -> v_t { return eve::radinpi(std::acos(1/e)); };
  auto dasecpi = [](auto e) -> v_t { return eve::radinpi(v_t(1)/(std::abs(e)*std::sqrt(e*e-1))); };
  TTS_ULP_EQUAL(eve::asecpi(a0)           , map(sasecpi, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecpi)(a0), map(dasecpi, a0), 2);
  TTS_ULP_EQUAL(eve::asecpi(a1)           , map(sasecpi, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecpi)(a1), map(dasecpi, a1), 2);
  TTS_ULP_EQUAL(eve::asecpi(a2)           , map(sasecpi, a2), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecpi)(a2), map(dasecpi, a2), 2);
  TTS_ULP_EQUAL(eve::asecpi(a3)           , map(sasecpi, a3), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asecpi)(a3), map(dasecpi, a3), 2);

};
