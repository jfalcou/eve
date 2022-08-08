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
TTS_CASE_TPL("Check return types of eve::is_real(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_real(T()), logical<T>);
  TTS_EXPR_IS(eve::is_real(v_t()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::is_real
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::is_real(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)))
<typename T>(T const& a0) { TTS_EQUAL(eve::is_real(a0), eve::true_(eve::as(a0))); };
