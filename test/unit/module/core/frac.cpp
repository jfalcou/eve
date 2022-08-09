//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::frac(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::frac(T()), T);

  TTS_EXPR_IS(eve::frac(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::frac
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::frac(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::frac(a0), map([](auto e) -> v_t { return e - std::trunc(e); }, a0));
};
