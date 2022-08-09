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
TTS_CASE_TPL("Check return types of eve::is_nan(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_nan(T()), logical<T>);
  TTS_EXPR_IS(eve::is_nan(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_nan
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_nan(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nan(a0), map([](auto e) -> eve::logical<v_t> { return (e != e); }, a0));
  TTS_EQUAL(eve::is_nan[t](a0), eve::if_else(t, eve::is_nan(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::is_nan on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using eve::as;
  auto cases = tts::limits(tgt);

  TTS_EQUAL(eve::is_nan(cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_nan(cases.minf), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_nan(cases.inf), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_nan(cases.mzero), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_nan(cases.valmin), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_nan(cases.valmax), eve::false_(as<T>()));
};
