//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/diff/acosd.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acosd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acosd(T())  , T);
  TTS_EXPR_IS( eve::acosd(v_t()), v_t);
};

//==================================================================================================
// acosd  tests
//==================================================================================================
EVE_TEST( "Check behavior of acosd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1, 1))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acosd(a0)      , map([](auto e) -> v_t { return eve::radindeg(std::acos(e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acosd)(a0), map([](auto e) -> v_t { return  -eve::radindeg(1.0)/std::sqrt(1-e*e); }, a0), 2);
};
