//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_TPL("Check (eve::ifrexp behavior", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using i_t = eve::as_integer_t<T, signed>;
  {
    auto [p0, p1] = eve::ifrexp(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp(T(0));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, i_t(0));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::pedantic](T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::pedantic](T(0));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, i_t(0));
  }
  if constexpr( eve::platform::supports_nans )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::nan(eve::as<T>())));
    TTS_EQUAL(r1, (i_t(0)));
  }
  if constexpr( eve::platform::supports_infinites )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::inf(eve::as<T>()));
    auto [q0, q1] = eve::ifrexp[eve::pedantic](eve::minf(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<T>())));
    TTS_EQUAL(r1, i_t(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<T>())));
    TTS_EQUAL(q1, i_t(0));
  }
  if constexpr( eve::platform::supports_denormals )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::mindenormal(eve::as<T>()));

    TTS_ULP_EQUAL(r0, T(0.5), 1);
    TTS_EQUAL(r1, i_t(eve::minexponent(eve::as<T>()) - eve::nbmantissabits(eve::as<T>()) + 1));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::raw](T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
};
