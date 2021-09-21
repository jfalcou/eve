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
#include <eve/function/acot.hpp>
#include <eve/function/diff/acot.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acot"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acot(T())  , T);
  TTS_EXPR_IS( eve::acot(v_t()), v_t);
};

//==================================================================================================
// acot  tests
//==================================================================================================
EVE_TEST( "Check behavior of acot on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(-100.0, 100.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acot(a0)      , map([](auto e) -> v_t { return std::atan(1/e); }, a0), 2);
  TTS_ULP_EQUAL(eve::acot(a1)      , map([](auto e) -> v_t { return std::atan(1/e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acot)(a0), map([](auto e) -> v_t { return  -v_t(1)/(e*e+1); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acot)(a1), map([](auto e) -> v_t { return  -v_t(1)/(e*e+1); }, a1), 2);
};
