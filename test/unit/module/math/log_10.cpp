//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of log_10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::log_10(as<T>())  , T);
  TTS_EXPR_IS( eve::log_10(as<v_t>()), v_t);
};

//==================================================================================================
// log_10  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of log_10 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
    using elt_t = eve::element_type_t<T>;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    TTS_EXPECT(downward(eve::log_10)(as<elt_t>()) < std::log(10.0l));
    TTS_EXPECT(upward(eve::log_10)(as<elt_t>())   > std::log(10.0l));
  }
  TTS_ULP_EQUAL(eve::log_10(as<T>()), T(std::log(10.0l)), 0.0);
  TTS_EXPECT(eve::all(downward(eve::log_10)(as<T>()) <= eve::log_10(as<T>())));
  TTS_EXPECT(eve::all(eve::log_10(as<T>()) <= upward(eve::log_10)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::log_10)(as<T>()), upward(eve::log_10)(as<T>()), 0.5);
};
