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
TTS_CASE_TPL( "Check return types of log10_e"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::log10_e(as<T>())  , T);
  TTS_EXPR_IS( eve::log10_e(as<v_t>()), v_t);
};

//==================================================================================================
// log10_e  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of log10_e on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

    using elt_t = eve::element_type_t<T>;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    TTS_EXPECT(downward(eve::log10_e)(as<elt_t>()) < std::log10(std::exp(1.0l)));
    TTS_EXPECT(upward(eve::log10_e)(as<elt_t>())   > std::log10(std::exp(1.0l)));
  }
  TTS_ULP_EQUAL(eve::log10_e(as<T>()), T(std::log10(std::exp(1.0l))), 0.0);
  TTS_EXPECT(eve::all(downward(eve::log10_e)(as<T>()) <= eve::log10_e(as<T>())));
  TTS_EXPECT(eve::all(eve::log10_e(as<T>()) <= upward(eve::log10_e)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::log10_e)(as<T>()), upward(eve::log10_e)(as<T>()), 0.5);
};
