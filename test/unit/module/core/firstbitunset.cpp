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
TTS_CASE_TPL("Check return types of eve::firstbitunset(simd)", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::firstbitunset(T()), T);
  TTS_EXPR_IS(eve::firstbitunset(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::firstbitunset
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::firstbitunset(simd)",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::ramp(0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, const M t)
{
  using eve::detail::map;
  using vi_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::firstbitunset(a0), map([](auto e) -> vi_t { return eve::firstbitunset(e); }, a0));
  TTS_EQUAL(eve::firstbitunset[t](a0), eve::if_else(t, eve::firstbitunset(a0), a0));
};
