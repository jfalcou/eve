//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::epsilon(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::epsilon(T()), T);
  TTS_EXPR_IS(eve::epsilon(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::epsilon
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::epsilon(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(1)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::as;
  if constexpr( eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_ULP_EQUAL(eve::epsilon(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::epsilon(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::epsilon(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    }
    TTS_ULP_EQUAL(eve::epsilon(T(1)), eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(0)), eve::mindenormal(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(10)), 8 * eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(5)), 4 * eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(2)), 2 * eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(1.5)), eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(a0),
                  map([](auto e) -> v_t { return eve::bit_floor(e) * eve::eps(as<v_t>()); }, a0),
                  2);
  }
  else
  {
    TTS_ULP_EQUAL(eve::epsilon(T(1)), T(1), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(10)), T(1), 0.5);
  }
};
