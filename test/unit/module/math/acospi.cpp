//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/acospi.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/function/diff/acospi.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acospi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acospi(T())  , T);
  TTS_EXPR_IS( eve::acospi(v_t()), v_t);
};

//==================================================================================================
// acospi  tests
//==================================================================================================
EVE_TEST( "Check behavior of acospi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1, 1))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acospi(a0)      , map([](auto e) -> v_t { return eve::radinpi(std::acos(e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acospi)(a0), map([](auto e) -> v_t { return  -eve::radinpi(1.0)/std::sqrt(1-e*e); }, a0), 2);
};
