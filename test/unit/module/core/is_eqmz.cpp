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
TTS_CASE_TPL("Check return types of eve::is_eqmz(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_eqmz(T()), logical<T>);
  TTS_EXPR_IS(eve::is_eqmz(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_eqmz
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_eqmz(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_eqmz(a0), tts::map([](auto e) -> eve::logical<v_t> { return e == 0 && eve::is_negative(e); }, a0));
  TTS_EQUAL(eve::is_eqmz[t](a0), eve::if_else(t, eve::is_eqmz(a0), eve::false_(eve::as(a0))));
};
