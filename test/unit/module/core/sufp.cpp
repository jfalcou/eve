//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sufp(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sufp(T()), T);
  TTS_EXPR_IS(eve::sufp(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sufp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sufp(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(1)))
<typename T>(T const& )
{
  using eve::as;
  if constexpr( eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_ULP_EQUAL(eve::sufp(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sufp(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sufp(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sufp[eve::harrisson](eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sufp[eve::harrisson](eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sufp[eve::harrisson](eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    }
    auto ufp = [](auto x){ return eve::exp2(eve::floor(eve::log2(eve::abs(x)))); };
    TTS_ULP_EQUAL(eve::sufp(T(1)), ufp(T(1)), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(0)), eve::mindenormal(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(10)), ufp(T(10)), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(5)), ufp(T(5)), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(2)), ufp(T(2)), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(1.5)), ufp(T(1.5)), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(1000.5)), ufp(T(1000.5)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(1)), ufp(T(1)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(0)), ufp(T(0)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(10)),2*ufp(T(10)) , 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(5)), 2*ufp(T(5)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(2)), ufp(T(2)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(1.5)), 2*ufp(T(1.5)), 0.5);
    TTS_ULP_EQUAL(eve::sufp[eve::harrisson](T(1000.5)), 2*ufp(T(1000.5)), 0.5);
  }
  else
  {
    TTS_ULP_EQUAL(eve::sufp(T(1)), T(1), 0.5);
    TTS_ULP_EQUAL(eve::sufp(T(10)), T(8), 0.5);
  }
};
