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
TTS_CASE_TPL("Check return types of eve::is_nemz(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_nemz(T()), logical<T>);
  TTS_EXPR_IS(eve::is_nemz(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_nemz
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_nemz(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nemz(a0), map([](auto e) -> eve::logical<v_t> { return eve::is_ltz(e) || eve::is_positive(e); }, a0));
  TTS_EQUAL(eve::is_nemz[t](a0), eve::if_else(t, eve::is_nemz(a0), eve::false_(eve::as(a0))));
};
