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
TTS_CASE_TPL("Check return types of eve::signnz", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::signnz(T()), T);
  TTS_EXPR_IS(eve::signnz[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::signnz[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::signnz[bool()](T()), T);

  TTS_EXPR_IS(eve::signnz(v_t()), v_t);
  TTS_EXPR_IS(eve::signnz[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::signnz[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::signnz[bool()](v_t()), v_t);

  if constexpr( eve::floating_real_value<T> ) {}
};

//==================================================================================================
// Tests for eve::signnz
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::signnz(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(-10, +10), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::signnz(a0), map([](auto e) -> v_t { return e >= 0 ? 1 : -1; }, a0));
  TTS_EQUAL(eve::signnz[mask](a0), eve::if_else(mask, eve::signnz(a0), a0));
  if constexpr( eve::floating_real_value<T> )
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::signnz)(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
  }
};
