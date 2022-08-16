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
TTS_CASE_TPL("Check return types of cos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinpicospi(T()), (kumi::tuple<T, T>));
  TTS_EXPR_IS(eve::sinpicospi(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mmed = []<typename T>(eve::as<T> const& tgt)
{ return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };
auto med = []<typename T>(eve::as<T> const& tgt)
{ return eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt) * eve::inv_pi(tgt); };

TTS_CASE_WITH("Check behavior of cos on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.25, 0.25),
                            tts::randoms(-0.5, 0.5),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::sinpicospi;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return eve::cospi(e); };
  auto refs = [](auto e) -> v_t { return eve::sinpi(e); };
  {
    auto [s, c] = eve::quarter_circle(sinpicospi)(a0);
    TTS_ULP_EQUAL(s, map(refs, a0), 2);
    TTS_ULP_EQUAL(c, map(refc, a0), 2);
  }
  {
    auto [s, c] = eve::half_circle(sinpicospi)(a0);
    TTS_ULP_EQUAL(s, map(refs, a0), 2);
    TTS_ULP_EQUAL(c, map(refc, a0), 2);
    auto [s1, c1] = eve::half_circle(sinpicospi)(a1);
    TTS_ULP_EQUAL(s1, map(refs, a1), 2);
    TTS_ULP_EQUAL(c1, map(refc, a1), 2);
  }
  {
    auto [s, c] = sinpicospi(a0);
    TTS_ULP_EQUAL(s, map(refs, a0), 2);
    TTS_ULP_EQUAL(c, map(refc, a0), 2);
    auto [s1, c1] = sinpicospi(a1);
    TTS_ULP_EQUAL(s1, map(refs, a1), 2);
    TTS_ULP_EQUAL(c1, map(refc, a1), 2);
    auto [s2, c2] = sinpicospi(a2);
    TTS_ULP_EQUAL(s2, map(refs, a2), 2);
    TTS_ULP_EQUAL(c2, map(refc, a2), 2);
    auto [s3, c3] = sinpicospi(a3);
    TTS_ULP_EQUAL(s3, map(refs, a3), 2);
    TTS_ULP_EQUAL(c3, map(refc, a3), 2);
  }
};
