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
#include <eve/function/asech.hpp>
#include <eve/function/diff/asech.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asech"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asech(T())  , T);
  TTS_EXPR_IS( eve::asech(v_t()), v_t);
};

//==================================================================================================
// asech  tests
//==================================================================================================
EVE_TEST( "Check behavior of asech on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::asech(a0)      , map([](auto e) -> v_t { return std::acosh(1/e); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::asech)(a0), map([](auto e) -> v_t { return  v_t(-1)/(e*std::sqrt(1-e*e)); }, a0), 2);
};
