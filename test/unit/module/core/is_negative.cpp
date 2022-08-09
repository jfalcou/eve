//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_negative(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_negative(T()), logical<T>);
  TTS_EXPR_IS(eve::is_negative(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_negative
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_negative(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0.0), tts::logicals(0, 3)))
<typename T, typename M>(T a0, M const& t)
{
  using eve::as;
  using eve::bit_or;
  using eve::bitofsign;
  using eve::one;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_negative(a0),
            map([](auto e) -> eve::logical<v_t>
                { return bit_or(bitofsign(e), one(as(e))) < v_t(0); },
                a0));
  TTS_EQUAL(eve::is_negative(-a0),
            map([](auto e) -> eve::logical<v_t>
                { return bit_or(bitofsign(e), one(as(e))) < v_t(0); },
                -a0));
  TTS_EQUAL(eve::is_negative[t](a0),
            eve::if_else(t, eve::is_negative(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::is_negative on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{
  using eve::as;

  auto cases = tts::limits(tgt);
  TTS_EQUAL(eve::is_negative(cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_negative(-cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.minf), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.inf), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.zero), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.mzero), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.valmin), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_negative(cases.valmax), eve::false_(as<T>()));
};
