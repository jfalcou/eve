//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sub", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::sub(T(), T()), T);
  TTS_EXPR_IS(eve::sub(T(), v_t()), T);
  TTS_EXPR_IS(eve::sub(v_t(), T()), T);
  TTS_EXPR_IS(eve::sub(v_t(), v_t()), v_t);

  // saturated
  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::sub[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<T>()])(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<T>()])(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<T>()])(v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<v_t>()])(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<v_t>()])(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub[eve::logical<v_t>()])(v_t(), T()), T);

  // multi
  TTS_EXPR_IS(eve::sub(T(), T(), T()), T);
  TTS_EXPR_IS(eve::sub(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::sub(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub(v_t(), v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::sub)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//==  sub simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sub on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::saturated;
  using eve::sub;
  using eve::detail::map;

  TTS_EQUAL(sub(a0, a2), map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL(saturated(sub)(a0, a2),
            map([&](auto e, auto f) { return saturated(sub)(e, f); }, a0, a2));
  TTS_EQUAL(sub(a0, a1, a2),
            map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(saturated(sub)(a0, a1, a2),
            map([&](auto e, auto f, auto g) { return saturated(sub)(saturated(sub)(e, f), g); },
                a0,a1,a2)
            );
};

//==================================================================================================
//==  conditional sub tests on simd
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; };

TTS_CASE_WITH("Check behavior of sub on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::saturated;
  using eve::sub;
  using eve::detail::map;
  TTS_EQUAL(sub[a2 > T(64)](a0, a1),
            map([](auto e, auto f, auto g) { return g > 64 ? sub(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(
      saturated(sub[a2 > T(64)])(a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? saturated(sub)(e, f) : e; }, a0, a1, a2));
};

/// TODO waiting for interface simplifications to add scalar tests
