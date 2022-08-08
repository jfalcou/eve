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

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrt", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sqrt(T()), T);
  TTS_EXPR_IS(eve::sqrt(v_t()), v_t);
  TTS_EXPR_IS(eve::sqrt[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::sqrt[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::sqrt[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::sqrt[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::sqrt[bool()](T()), T);
  TTS_EXPR_IS(eve::sqrt[bool()](v_t()), v_t);
};

//==================================================================================================
// sqrt simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sqrt(wide) and diff on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::rec;
  using eve::sqr;
  TTS_ULP_EQUAL(eve::sqrt(a0), map([&](auto e) { return std::sqrt(e); }, a0), 2);
};

//==================================================================================================
// sqrt[cond](simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sqrt[cond](wide) on  floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, eve::valmax)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  auto val  = eve::unsigned_value<v_t> ? (eve::valmax(eve::as<v_t>()) / 2) : 0;
  using eve::detail::map;
  TTS_ULP_EQUAL(
      eve::sqrt[a0 < val](a0), map([&](auto e) { return (e < val) ? std::sqrt(e) : e; }, a0), 2);
};
