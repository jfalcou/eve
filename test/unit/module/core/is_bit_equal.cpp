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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_bit_equal(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  using ui_t= eve::as_integer_t<T, unsigned>;
  using vi_t= eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS(eve::is_bit_equal(T(), T()), logical<ui_t>);
  TTS_EXPR_IS(eve::is_bit_equal(v_t(), v_t()), logical<vi_t>);
  TTS_EXPR_IS(eve::is_bit_equal(T(), v_t()), logical<ui_t>);
  TTS_EXPR_IS(eve::is_bit_equal(v_t(), T()), logical<ui_t>);
  TTS_EXPR_IS(eve::is_bit_equal(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::is_bit_equal(logical<v_t>(), logical<v_t>()), logical<v_t>);
};

//==================================================================================================
//== Tests for eve::is_bit_equal
//==================================================================================================
TTS_CASE_WITH(
    "Check behavior of eve::is_bit_equal(simd)",
    eve::test::simd::all_types,
    tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3), tts::logicals(1, 2)))
<typename T, typename M>(T const& a0, T const& a1, M const& l0, M const& l1)
{
  using eve::as;
  using eve::bit_cast;
  using v_t = eve::element_type_t<T>;
  using vi_t= eve::as_integer_t<v_t, unsigned>;
  using bi_t= eve::as_integer_t<T, unsigned>;
  TTS_EQUAL(eve::is_bit_equal(a0, a1),
            tts::map([](auto e, auto f) -> eve::logical<vi_t> { return bit_cast(e, as<vi_t>())== bit_cast(f, as<vi_t>()); }, a0, a1));
  TTS_EQUAL(eve::is_bit_equal(a0, a0),
            tts::map([](auto e, auto f) -> eve::logical<vi_t> { return bit_cast(e, as<vi_t>())== bit_cast(f, as<vi_t>()); }, a0, a0));
  TTS_EQUAL(eve::is_bit_equal(l0, l1),
             tts::map([](auto e, auto f) { return e == f; }, l0, l1));
  TTS_EQUAL(eve::is_bit_equal[l0](a0, a1),
            eve::if_else(l0, eve::is_bit_equal(a0, a1), eve::false_(eve::as<bi_t>())));
};

//==================================================================================================
//== Tests for eve::is_bit_equal corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_bit_equal(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{

  using bi_t= eve::as_integer_t<T, unsigned>;
  auto cases = tts::limits(tgt);
  TTS_EQUAL(eve::is_bit_equal(cases.nan, cases.nan), eve::true_(eve::as<bi_t>()));
  TTS_EQUAL(eve::is_bit_equal(cases.mzero, cases.mzero), eve::true_(eve::as<bi_t>()));
  TTS_EQUAL(eve::is_bit_equal(cases.mzero, cases.zero), eve::false_(eve::as<bi_t>()));

};
