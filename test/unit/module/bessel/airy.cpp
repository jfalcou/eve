//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/bessel.hpp>

#include <boost/math/special_functions/airy.hpp>

TTS_CASE_TPL("Check return types of airy_ai", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using kv_t = kumi::tuple<v_t, v_t>;
  using kT   = kumi::tuple<T, T>;
  TTS_EXPR_IS(eve::airy(T(0)), kT);
  TTS_EXPR_IS(eve::airy(v_t(0)), kv_t);
};

TTS_CASE_WITH("Check behavior of airy on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-20.0, 0.0), tts::randoms(0.0, 20.0)))
<typename T>(T a0, T a1)
{
  using v_t        = eve::element_type_t<T>;
  v_t  abstol      = 1000 * eve::eps(eve::as<v_t>());
  auto eve_airy    = [](auto x) { return eve::airy(x); };
  auto std_airy_ai = [](auto x) -> v_t { return eve::airy_ai(x); };
  auto std_airy_bi = [](auto x) -> v_t { return eve::airy_bi(x); };

  {
    auto [ai, bi] = eve_airy(a0);
    TTS_ABSOLUTE_EQUAL(ai, map(std_airy_ai, a0), abstol);
    TTS_RELATIVE_EQUAL(bi, map(std_airy_bi, a0), 0.0004);
  }
  {
    auto [ai, bi] = eve_airy(a1);
    TTS_ABSOLUTE_EQUAL(ai, map(std_airy_ai, a1), abstol);
    TTS_RELATIVE_EQUAL(bi, map(std_airy_bi, a1), 0.0004);
  }
};
