//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of rem", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // downward
  TTS_EXPR_IS(eve::rem[eve::downward](T(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::downward](T(), v_t()), T);
  TTS_EXPR_IS(eve::rem[eve::downward](v_t(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::downward](v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::rem[eve::upward](T(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::upward](T(), v_t()), T);
  TTS_EXPR_IS(eve::rem[eve::upward](v_t(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::upward](v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::rem[eve::to_nearest](T(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::to_nearest](T(), v_t()), T);
  TTS_EXPR_IS(eve::rem[eve::to_nearest](v_t(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::to_nearest](v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::rem[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::rem[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::rem[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::rem[eve::logical<v_t>()](v_t(), T()), T);
};

//==================================================================================================
//==  rem simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of rem on wide",
              eve::test::simd::integers // all_types
              ,
              tts::generate(tts::randoms(1, 100), tts::randoms(1, 11), tts::randoms(1, 11)))
<typename T>(T a0, T, T a2)
{
  using eve::downward;
  using eve::rem;
  using eve::to_nearest;
  using eve::upward;
  using eve::detail::map;
  a2 = eve::if_else(eve::is_eqz(a2), eve::one, a2);

  TTS_EQUAL(eve::rem(a0, a2), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a2));
  TTS_EQUAL(rem[downward](a0, a2),  map([&](auto e, auto f) { return rem[downward](e, f); }, a0, a2));
  TTS_EQUAL(rem[upward](a0, a2), map([&](auto e, auto f) { return rem[upward](e, f); }, a0, a2));
  TTS_EQUAL(rem[to_nearest](a0, a2), map([&](auto e, auto f) { return rem[to_nearest](e, f); }, a0, a2));
};

//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::rem variants on wide",
             eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using eve::downward;
  using eve::rem;
  using eve::to_nearest;
  using eve::upward;
  using v_t = eve::element_type_t<T>;

  // downward
  TTS_EQUAL(eve::rem[downward](T(-1), T(2)), T(1));
  TTS_EQUAL(eve::rem[downward](v_t(-1), T(2)), T(1));
  TTS_EQUAL(eve::rem[downward](T(-1), v_t(2)), T(1));
  TTS_EQUAL(eve::rem[downward](T(-4), T(3)), T(2));
  TTS_EQUAL(eve::rem[downward](v_t(-4), T(3)), T(2));
  TTS_EQUAL(eve::rem[downward](T(-4), v_t(3)), T(2));

  TTS_EQUAL(eve::rem[downward](T(1), T(-2)), T(-1));
  TTS_EQUAL(eve::rem[downward](v_t(1), T(-2)), T(-1));
  TTS_EQUAL(eve::rem[downward](T(1), v_t(-2)), T(-1));
  TTS_EQUAL(eve::rem[downward](T(4), T(-3)), T(-2));
  TTS_EQUAL(eve::rem[downward](v_t(4), T(-3)), T(-2));
  TTS_EQUAL(eve::rem[downward](T(4), v_t(-3)), T(-2));

  TTS_EQUAL(eve::rem[downward](T {12}, T(4)), T(0));
  TTS_EQUAL(eve::rem[downward](T(1), T(2)), T(1));
  TTS_EQUAL(eve::rem[downward](T(4), T(3)), T(1));
  TTS_EQUAL(eve::rem[downward](T(4), T(4)), T(0));

  TTS_EQUAL(eve::rem[downward](v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::rem[downward](v_t(1), T(2)), T(1));
  TTS_EQUAL(eve::rem[downward](v_t(4), T(3)), T(1));

  TTS_EQUAL(eve::rem[downward](T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::rem[downward](T(1), v_t(2)), T(1));
  TTS_EQUAL(eve::rem[downward](T(4), v_t(3)), T(1));

  // upward
  TTS_EQUAL(eve::rem[eve::upward](T(-1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](v_t(-1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](T(-1), v_t(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](T(-4), T(3)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](v_t(-4), T(3)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](T(-4), v_t(3)), T(-1));

  TTS_EQUAL(eve::rem[eve::upward](T(1), T(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::upward](v_t(1), T(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::upward](T(1), v_t(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::upward](T(4), T(-3)), T(1));
  TTS_EQUAL(eve::rem[eve::upward](v_t(4), T(-3)), T(1));
  TTS_EQUAL(eve::rem[eve::upward](T(4), v_t(-3)), T(1));

  TTS_EQUAL(eve::rem[eve::upward](T {12}, T(4)), T(0));
  TTS_EQUAL(eve::rem[eve::upward](T(1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](T(4), T(3)), T(-2));

  TTS_EQUAL(eve::rem[eve::upward](v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::rem[eve::upward](v_t(1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](v_t(4), T(3)), T(-2));

  TTS_EQUAL(eve::rem[eve::upward](T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::rem[eve::upward](T(1), v_t(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::upward](T(4), v_t(3)), T(-2));

  // to_nearest
  TTS_EQUAL(eve::rem[eve::to_nearest](T(-1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(-1), T(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(-1), v_t(2)), T(-1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(-4), T(3)), T(-1));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(-4), T(3)), T(-1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(-4), v_t(3)), T(-1));

  TTS_EQUAL(eve::rem[eve::to_nearest](T(1), T(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(1), T(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(1), v_t(-2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(4), T(-3)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(4), T(-3)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(4), v_t(-3)), T(1));

  TTS_EQUAL(eve::rem[eve::to_nearest](T {12}, T(4)), T(0));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(1), T(2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(4), T(3)), T(1));

  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(1), T(2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](v_t(4), T(3)), T(1));

  TTS_EQUAL(eve::rem[eve::to_nearest](T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(1), v_t(2)), T(1));
  TTS_EQUAL(eve::rem[eve::to_nearest](T(4), v_t(3)), T(1));
};

//==================================================================================================
//==  conditional rem tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; };

TTS_CASE_WITH("Check behavior of rem on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127)))
<typename T>(T a0, T a1, T a2)
{
  using eve::downward;
  using eve::is_nez;
  using eve::rem;
  using eve::to_nearest;
  using eve::upward;
  using eve::detail::map;

  TTS_RELATIVE_EQUAL( rem[is_nez(a2)][downward](a0, a2), map([](auto e, auto f) { return is_nez(f) ? rem[downward](e, f) : e; }, a0, a2),  4e-4);
  TTS_RELATIVE_EQUAL(rem[is_nez(a2)][upward](a0, a2), map([](auto e, auto f) { return is_nez(f) ? rem[upward](e, f) : e; }, a0, a2),       4e-4);
  TTS_RELATIVE_EQUAL(rem[is_nez(a2)][to_nearest](a0, a2), map([](auto e, auto f) { return is_nez(f) ? rem[to_nearest](e, f) : e; }, a0, a2), 4e-4);

  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_RELATIVE_EQUAL(rem[a2 > T(64)][downward](a0, a1), map([](auto e, auto f, auto g) { return g > 64 ? rem[downward](e, f) : e; }, a0, a1, a2), 4e-4);
  TTS_RELATIVE_EQUAL(rem[a2 > T(64)][upward](a0, a1),   map([](auto e, auto f, auto g) { return g > 64 ? rem[upward](e, f) : e; }, a0, a1, a2),   4e-4);
  TTS_RELATIVE_EQUAL(rem[a2 > T(64)][to_nearest](a0, a1), map([](auto e, auto f, auto g) { return g > 64 ? rem[to_nearest](e, f) : e; }, a0, a1, a2), 4e-4);
};
