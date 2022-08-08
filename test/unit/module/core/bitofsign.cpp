//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bitofsign", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::bitofsign(T()), T);
  TTS_EXPR_IS(eve::bitofsign(v_t()), v_t);
  TTS_EXPR_IS(eve::bitofsign[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::bitofsign[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS(eve::bitofsign[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::bitofsign[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::bitofsign[bool()](T()), T);
  TTS_EXPR_IS(eve::bitofsign[bool()](v_t()), v_t);
};

//==================================================================================================
// bitofsign(simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bitofsign(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  TTS_EQUAL(eve::bitofsign(a0),
            map([&](auto e) { return eve::bit_and(e, eve::signmask(eve::as(e))); }, a0));
};

//==================================================================================================
// bitofsign[cond](simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bitofsign(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  auto val  = eve::unsigned_value<v_t> ? (eve::valmax(eve::as<v_t>()) / 2) : 0;
  using eve::detail::map;
  TTS_EQUAL(
      eve::bitofsign[a0 < val](a0),
      map([&](auto e) { return (e < val) ? eve::bit_and(e, eve::signmask(eve::as(e))) : e; }, a0));
};
