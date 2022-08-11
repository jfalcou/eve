//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_not_denormal(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_not_denormal(T()), logical<T>);
  TTS_EXPR_IS(eve::is_not_denormal(v_t()), logical<v_t>);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of is_not_denormal on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{
  using eve::as;
  using eve::is_not_denormal;

  auto cases = tts::limits(tgt);

  if constexpr( eve::platform::supports_denormals )
  {
    TTS_EQUAL(is_not_denormal(cases.smallestposval / 2), eve::false_(as<T>()));
    TTS_EQUAL(is_not_denormal(cases.mindenormal), eve::false_(as<T>()));
  }
  TTS_IEEE_EQUAL(is_not_denormal(cases.inf), eve::true_(as<T>()));
  TTS_IEEE_EQUAL(is_not_denormal(cases.minf), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.mzero), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.zero), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.smallestposval), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.valmin), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.one), eve::true_(as<T>()));
  TTS_EQUAL(is_not_denormal(cases.mone), eve::true_(as<T>()));
};
