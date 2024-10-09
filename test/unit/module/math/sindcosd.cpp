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

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sindcosd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sindcosd(T()), (eve::wide<kumi::tuple<v_t, v_t>,typename T::cardinal_type>));
  TTS_EXPR_IS(eve::sindcosd(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// sindcosd  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sindcosd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-45, 45), tts::randoms(-90, 90), tts::randoms(-360, 360)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::sindcosd;

  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return eve::cosd(e); };
  auto refs = [](auto e) -> v_t { return eve::sind(e); };
  {
    auto [s, c] = sindcosd[eve::quarter_circle](a0);
    TTS_ULP_EQUAL(s, tts::map(refs, a0), 2);
    TTS_ULP_EQUAL(c, tts::map(refc, a0), 2);
  }
  {
    auto [s, c] = sindcosd(a0);
    TTS_ULP_EQUAL(s, tts::map(refs, a0), 2);
    TTS_ULP_EQUAL(c, tts::map(refc, a0), 2);
    auto [s1, c1] = sindcosd(a1);
    TTS_ULP_EQUAL(s1, tts::map(refs, a1), 2);
    TTS_ULP_EQUAL(c1, tts::map(refc, a1), 30);
    auto [s2, c2] = sindcosd(a2);
    TTS_ULP_EQUAL(s2, tts::map(refs, a2), 51);
    TTS_ULP_EQUAL(c2, tts::map(refc, a2), 51);
  }
};
