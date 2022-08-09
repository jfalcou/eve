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
TTS_CASE_TPL("Check return types of eve::firstbitset(simd)", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::firstbitset(T()), T);
  TTS_EXPR_IS(eve::firstbitset(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::firstbitset
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::firstbitset(simd)",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, const M t)
{
  using eve::detail::map;
  using vi_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::firstbitset(a0), map([](auto e) -> vi_t { return eve::firstbitset(e); }, a0));
  TTS_EQUAL(eve::firstbitset[t](a0), eve::if_else(t, eve::firstbitset(a0), a0));
};
