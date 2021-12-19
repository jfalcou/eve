//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/acscpi.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/function/diff/acscpi.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acscpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acscpi(T())  , T);
  TTS_EXPR_IS( eve::acscpi(v_t()), v_t);
};

//==================================================================================================
// acscpi  tests
//==================================================================================================
EVE_TEST( "Check behavior of acscpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(1.0    , 100.0 )
                              , eve::test::randoms(1.0    , 1e20  )
                              , eve::test::randoms(-1e20  , -1.0  )
                              , eve::test::randoms(-100.0 , -1.0  )
                              )
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sacscpi = [](auto e) -> v_t { return eve::radinpi(std::asin(1/e)); };
  auto dacscpi = [](auto e) -> v_t { return eve::radinpi(-v_t(1)/(std::abs(e)*std::sqrt(e*e-1))); };
  TTS_ULP_EQUAL(eve::acscpi(a0)           , map(sacscpi, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscpi)(a0), map(dacscpi, a0), 2);
  TTS_ULP_EQUAL(eve::acscpi(a1)           , map(sacscpi, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscpi)(a1), map(dacscpi, a1), 2);
  TTS_ULP_EQUAL(eve::acscpi(a2)           , map(sacscpi, a2), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscpi)(a2), map(dacscpi, a2), 2);
  TTS_ULP_EQUAL(eve::acscpi(a3)           , map(sacscpi, a3), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acscpi)(a3), map(dacscpi, a3), 2);
};
