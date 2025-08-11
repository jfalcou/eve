//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sulp(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sulp(T()), T);
  TTS_EXPR_IS(eve::sulp(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sulp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sulp(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(1)))
<typename T>(T const& )
{
  using eve::as;
  if constexpr( eve::floating_value<T>)// && (sizeof(eve::element_type_t<T>) == 8) && (eve::cardinal_v<T> == 1))
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_ULP_EQUAL(eve::sulp(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sulp(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sulp(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sulp[eve::harrisson](eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sulp[eve::harrisson](eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::sulp[eve::harrisson](eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    }
    using e_t = eve::element_type_t<T>;
    constexpr e_t nbmb(eve::nbmantissabits(eve::as<e_t>()));
    constexpr e_t mexp(eve:: minexponent(eve::as<e_t>())-1);

    auto ulp = [](auto x){
      return eve::if_else(eve::is_denormal(x), T(eve::exp2(mexp-nbmb)), eve::exp2(eve::floor(eve::log2(eve::abs(x)))-nbmb));
    };
    TTS_IEEE_EQUAL(eve::sulp(T(1)), ulp(T(1)));
    TTS_IEEE_EQUAL(eve::sulp(T(0)), T(0));
    TTS_IEEE_EQUAL(eve::sulp(T(10)),ulp(T(10)));
    TTS_IEEE_EQUAL(eve::sulp(T(5)), ulp(T(4)));
    TTS_IEEE_EQUAL(eve::sulp(T(2)), ulp(T(2)));
    TTS_IEEE_EQUAL(eve::sulp(T(1.5)),ulp(1.5));
    TTS_IEEE_EQUAL(eve::sulp(T(1000.6)), ulp(T(1000.6)));

    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(1)), ulp(T(1))/2);
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(0)), T(0));
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(10)),ulp(T(10)));
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(5)), ulp(T(4)));
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(2)), ulp(T(2))/2);
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(1.5)),ulp(T(1.5)));
    TTS_IEEE_EQUAL(eve::sulp[eve::harrisson](T(1000.5)), ulp(T(1000.5)));
  }
  else
  {
    TTS_EQUAL(eve::sulp(T(1)), T(1));
    TTS_EQUAL(eve::sulp(T(10)), T(1));
  }
};
