//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/asinh.hpp>
#include <eve/function/diff/asinh.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asinh"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asinh(T())  , T);
  TTS_EXPR_IS( eve::asinh(v_t()), v_t);
};

//==================================================================================================
// asinh  tests
//==================================================================================================
EVE_TEST( "Check behavior of asinh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asinh(a0)      , map([](auto e) -> v_t { return std::asinh(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asinh)(a0), map([](auto e) -> v_t { return  v_t(1)/std::sqrt(e*e+1); }, a0), 2);
};
