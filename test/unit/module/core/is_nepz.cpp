//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_nepz(simd)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_nepz(T()), logical<T>);
  TTS_EXPR_IS(eve::is_nepz(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_nepz
//==================================================================================================

TTS_CASE_TPL("Check behavior of eve::is_nepz (corner cases)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T> tgt)
{
  const auto cases = tts::limits(tgt);

  TTS_EQUAL(eve::is_nepz(cases.nan), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.inf), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.minf), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.mzero), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.zero), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.valmin), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_nepz(cases.valmax), eve::true_(eve::as<T>()));
};

TTS_CASE_WITH("Check behavior of eve::is_nepz(simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nepz(a0), tts::map([](auto e) -> eve::logical<v_t> { return !eve::is_eqpz(e); }, a0));
  TTS_EQUAL(eve::is_nepz[t](a0), eve::if_else(t, eve::is_nepz(a0), eve::false_(eve::as(a0))));
};
