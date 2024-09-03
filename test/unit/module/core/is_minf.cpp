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
TTS_CASE_TPL("Check return types of eve::is_minf(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_minf(T()), logical<T>);
  TTS_EXPR_IS(eve::is_minf(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_minf
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_minf(simd) integrals",
              eve::test::simd::integers,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T a0, M const& t)
{
  using eve::detail::map;
  TTS_EQUAL(eve::is_minf(a0), eve::false_(eve::as(a0)));
  TTS_EQUAL(eve::is_minf[t](a0),
            eve::if_else(t, eve::is_minf(a0), eve::false_(eve::as(a0))));
};

TTS_CASE_WITH("Check behavior of eve::is_minf(simd) IEEE",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0        = eve::if_else(eve::is_eqz(a0), eve::inf(eve::as<v_t>()), eve::zero);
  TTS_EQUAL(eve::is_minf(a0),
            map([](auto e) -> eve::logical<v_t> { return e - e != 0 && e < 0; }, a0));
  TTS_EQUAL(eve::is_minf[t](a0),
            eve::if_else(t, eve::is_minf(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::is_minf on wide",eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using eve::as;

  auto cases = tts::limits(tgt);
  TTS_EQUAL(eve::is_minf(cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(-cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.minf), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.inf), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.zero), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.mzero), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.valmin), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_minf(cases.valmax), eve::false_(as<T>()));
};
