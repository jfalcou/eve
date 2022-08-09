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
TTS_CASE_TPL("Check return types of eve::is_eqz(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_eqz(T()), logical<T>);
  TTS_EXPR_IS(eve::is_eqz(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_eqz
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_eqz(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_eqz(a0), map([](auto e) -> eve::logical<v_t> { return e == 0; }, a0));
  TTS_EQUAL(eve::is_eqz[t](a0), eve::if_else(t, eve::is_eqz(a0), eve::false_(eve::as(a0))));
};
