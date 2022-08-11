//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of add", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::add(T(), T()), T);
  TTS_EXPR_IS(eve::add(T(), v_t()), T);
  TTS_EXPR_IS(eve::add(v_t(), T()), T);
  TTS_EXPR_IS(eve::add(v_t(), v_t()), v_t);

  // saturated
  TTS_EXPR_IS(eve::saturated(eve::add)(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::add[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<T>()])(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<T>()])(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<T>()])(v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<v_t>()])(T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<v_t>()])(T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::add[eve::logical<v_t>()])(v_t(), T()), T);

  // multi
  TTS_EXPR_IS(eve::add(T(), T(), T()), T);
  TTS_EXPR_IS(eve::add(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::add(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add(v_t(), v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::saturated(eve::add)(T(), T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::saturated(eve::add)(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
//==  add simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of add on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::add;
  using eve::as;
  using eve::saturated;
  using eve::detail::map;

  TTS_EQUAL(add(a0, a2), map([](auto e, auto f) { return add(e, f); }, a0, a2));
  TTS_EQUAL(saturated(add)(a0, a2),
            map([&](auto e, auto f) { return saturated(add)(e, f); }, a0, a2));
  TTS_EQUAL(add(a0, a1, a2),
            map([&](auto e, auto f, auto g) { return add(add(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(saturated(add)(a0, a1, a2),
            map([&](auto e, auto f, auto g) { return saturated(add)(saturated(add)(e, f), g); },
                a0,
                a1,
                a2));
  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
//==  conditional add tests on simd
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T> const&)
                          { return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; });

TTS_CASE_WITH("Check behavior of add on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(mini, 127),
                            tts::randoms(mini, 127),
                            tts::randoms(mini, 127)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::add;
  using eve::saturated;
  using eve::detail::map;
  TTS_EQUAL(add[a2 > T(64)](a0, a1),
            map([](auto e, auto f, auto g) { return g > 64 ? add(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(
      saturated(add[a2 > T(64)])(a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? saturated(add)(e, f) : e; }, a0, a1, a2));
};
