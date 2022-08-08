//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_positive(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_positive(T()), logical<T>);
  TTS_EXPR_IS(eve::is_positive(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_positive
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_positive(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0.0)))
<typename T>(T const& a0)
{
  using eve::as;
  using eve::bit_or;
  using eve::bitofsign;
  using eve::one;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_positive(a0),
            map([](auto e) -> eve::logical<v_t>
                { return bit_or(bitofsign(e), one(as(e))) > v_t(0); },
                a0));
  TTS_EQUAL(eve::is_positive(-a0),
            map([](auto e) -> eve::logical<v_t>
                { return bit_or(bitofsign(e), one(as(e))) > v_t(0); },
                -a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::is_positive on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using eve::as;
  auto cases = tts::limits(tgt);

  TTS_EQUAL(eve::is_positive(cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_positive(-cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.minf), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.inf), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.zero), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.mzero), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.valmin), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_positive(cases.valmax), eve::true_(as<T>()));
};
