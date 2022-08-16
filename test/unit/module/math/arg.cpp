//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::arg(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::arg(T()), T);
  TTS_EXPR_IS(eve::pedantic(eve::arg)(T()), T);

  TTS_EXPR_IS(eve::arg(v_t()), v_t);
  TTS_EXPR_IS(eve::pedantic(eve::arg)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::arg
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::arg(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::arg(a0),
            map([](auto e) -> v_t { return e >= 0 ? 0 : eve::pi(eve::as(v_t())); }, a0));
};

//==================================================================================================
// Tests for eve::pedantic(eve::arg)
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::pedantic(eve::arg)(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto cases = tts::limits(tts::type<T> {});

  TTS_EQUAL(eve::pedantic(eve::arg)(a0),
            map([](auto e) -> v_t { return e >= 0 ? 0 : eve::pi(eve::as(v_t())); }, a0));
  TTS_IEEE_EQUAL(eve::pedantic(eve::arg)(cases.nan), cases.nan);
};
