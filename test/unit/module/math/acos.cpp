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
EVE_TEST_TYPES( "Check return types of acos"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acos(T())  , T);
  TTS_EXPR_IS( eve::acos(v_t()), v_t);
};

//==================================================================================================
// acos  tests
//==================================================================================================
EVE_TEST( "Check behavior of acos on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acos(a0)      , map([](auto e) -> v_t { return std::acos(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acos)(a0), map([](auto e) -> v_t { return  -v_t(1)/std::sqrt(1-e*e); }, a0), 2);
};
