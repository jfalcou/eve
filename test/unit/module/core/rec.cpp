//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::rec", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::rec(T()), T);
  TTS_EXPR_IS(eve::rec[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::rec[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::rec[bool()](T()), T);

  TTS_EXPR_IS(eve::rec(v_t()), v_t);
  TTS_EXPR_IS(eve::rec[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::rec[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::rec[bool()](v_t()), v_t);

  if constexpr( eve::floating_real_value<T> ) {}
};

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return -eve::smallestposval(tgt); });
auto maxi = tts::constant([](auto tgt) { return eve::valmax(tgt) / 2; });

//==================================================================================================
// Tests for eve::rec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rec(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(mini, maxi), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::rec(a0),
                map([](auto e) -> v_t { return e ? v_t(1 / e) : eve::valmax(eve::as<v_t>()); }, a0),
                2.5);

  TTS_EQUAL(eve::rec[mask](a0), eve::if_else(mask, eve::rec(a0), a0));
};
