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
TTS_CASE_TPL("Check return types of div", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // lower
  TTS_EXPR_IS(eve::div[eve::lower](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::lower](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::lower](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::lower](v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::div[eve::upper](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::upper](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::upper](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::upper](v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::div[eve::to_nearest](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::to_nearest](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::to_nearest](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::to_nearest](v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::div[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()](v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::div[eve::logical<T>()][eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<T>()][eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::logical<T>()][eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()][eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()][eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()][eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::div[eve::logical<v_t>()][eve::saturated](v_t(), v_t()), v_t);
};

//==================================================================================================
//==  div simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of div on wide",
              eve::test::simd::integers // all_types
              ,
              tts::generate(tts::randoms(0, 100), tts::randoms(1, 11), tts::randoms(1, 11)))
<typename T>(T a0, T, T a2)
{
  using eve::div;
  using eve::lower;
  using eve::to_nearest;
  using eve::upper;
  using eve::detail::map;
  a2 = eve::if_else(eve::is_eqz(a2), eve::one, a2);

  TTS_EQUAL(eve::div(a0, a2), map([](auto e, auto f) { return eve::div(e, f); }, a0, a2));
  TTS_EQUAL(div[lower](a0, a2), map([&](auto e, auto f) { return div[lower](e, f); }, a0, a2));
  TTS_EQUAL(div[upper](a0, a2), map([&](auto e, auto f) { return div[upper](e, f); }, a0, a2));
  TTS_EQUAL(div[to_nearest](a0, a2),  map([&](auto e, auto f) { return div[to_nearest](e, f); }, a0, a2));
};

//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::div variants on wide", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using eve::div;
  using eve::lower;
  using eve::to_nearest;
  using eve::upper;
  using v_t = eve::element_type_t<T>;

  // lower
  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(div[lower](T(-1), T(2)), T(-1));
    TTS_EQUAL(div[lower](v_t(-1), T(2)), T(-1));
    TTS_EQUAL(div[lower](T(-1), v_t(2)), T(-1));

    TTS_EQUAL(div[lower](T(-4), T(3)), T(-2));
    TTS_EQUAL(div[lower](v_t(-4), T(3)), T(-2));
    TTS_EQUAL(div[lower](T(-4), v_t(3)), T(-2));
    TTS_EQUAL(div[lower](T(-4), v_t(4)), T(-1));

    TTS_EQUAL(div[lower](T(4), T(-3)), T(-2));
    TTS_EQUAL(div[lower](v_t(4), T(-3)), T(-2));
    TTS_EQUAL(div[lower](T(4), v_t(-3)), T(-2));
    TTS_EQUAL(div[lower](T(4), v_t(-4)), T(-1));

    TTS_EQUAL(div[lower](T(-12), T(-4)), T(3));
    TTS_EQUAL(div[lower](T(-1), T(-2)), T(0));
    TTS_EQUAL(div[lower](T(-4), T(-3)), T(1));
    TTS_EQUAL(div[lower](T(-4), T(-4)), T(1));
    TTS_EQUAL(div[lower](T(0), T(-4)), T(0));
    TTS_EQUAL(div[lower](T(0), T(4)), T(0));
  }

  TTS_EQUAL(div[lower](T(12), T(4)), T(3));
  TTS_EQUAL(div[lower](T(1), T(2)), T(0));
  TTS_EQUAL(div[lower](T(4), T(3)), T(1));
  TTS_EQUAL(div[lower](T(4), T(4)), T(1));

  TTS_EQUAL(div[lower](v_t(12), T(4)), T(3));
  TTS_EQUAL(div[lower](v_t(1), T(2)), T(0));
  TTS_EQUAL(div[lower](v_t(4), T(3)), T(1));

  TTS_EQUAL(div[lower](T(12), v_t(4)), T(3));
  TTS_EQUAL(div[lower](T(1), v_t(2)), T(0));
  TTS_EQUAL(div[lower](T(4), v_t(3)), T(1));

  // upper
  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::div[upper](T(-1), T(2)), T(0));
    TTS_EQUAL(eve::div[upper](v_t(-1), T(2)), T(0));
    TTS_EQUAL(eve::div[upper](T(-1), v_t(2)), T(0));

    TTS_EQUAL(eve::div[upper](T(-4), T(3)), T(-1));
    TTS_EQUAL(eve::div[upper](v_t(-4), T(3)), T(-1));
    TTS_EQUAL(eve::div[upper](T(-4), v_t(3)), T(-1));
    TTS_EQUAL(eve::div[upper](T(-4), v_t(4)), T(-1));

    TTS_EQUAL(eve::div[upper](T(4), T(-3)), T(-1));
    TTS_EQUAL(eve::div[upper](v_t(4), T(-3)), T(-1));
    TTS_EQUAL(eve::div[upper](T(4), v_t(-3)), T(-1));
    TTS_EQUAL(eve::div[upper](T(4), v_t(-4)), T(-1));

    TTS_EQUAL(eve::div[upper](T(-12), T(-4)), T(3));
    TTS_EQUAL(eve::div[upper](T(-1), T(-2)), T(1));
    TTS_EQUAL(eve::div[upper](T(-4), T(-3)), T(2));
    TTS_EQUAL(eve::div[upper](T(-4), T(-4)), T(1));
    TTS_EQUAL(eve::div[upper](T(0), T(-4)), T(0));
    TTS_EQUAL(eve::div[upper](T(0), T(4)), T(0));
    TTS_EQUAL(eve::div[upper](T(1), T(2)), T(1));
  }

  TTS_EQUAL(eve::div[upper](T(12), T(4)), T(3));
  TTS_EQUAL(eve::div[upper](T(1), T(2)), T(1));
  TTS_EQUAL(eve::div[upper](T(4), T(3)), T(2));

  TTS_EQUAL(eve::div[upper](v_t(12), T(4)), T(3));
  TTS_EQUAL(eve::div[upper](v_t(1), T(2)), T(1));
  TTS_EQUAL(eve::div[upper](v_t(4), T(3)), T(2));

  TTS_EQUAL(eve::div[upper](T(12), v_t(4)), T(3));
  TTS_EQUAL(eve::div[upper](T(1), v_t(2)), T(1));
  TTS_EQUAL(eve::div[upper](T(4), v_t(3)), T(2));

  // nearest
  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::div[eve::to_nearest](T(-1), T(2)), T(0));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(-1), T(2)), T(0));
    TTS_EQUAL(eve::div[eve::to_nearest](T(-1), v_t(2)), T(0));
    TTS_EQUAL(eve::div[eve::to_nearest](T(1), T(-2)), T(0));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(1), T(-2)), T(0));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(1), v_t(-2)), v_t(0));
    TTS_EQUAL(eve::div[eve::to_nearest](T(-2), T(-2)), T(1));

    TTS_EQUAL(eve::div[eve::to_nearest](T(-3), T(2)), T(-2));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(-3), T(2)), T(-2));
    TTS_EQUAL(eve::div[eve::to_nearest](T(-3), v_t(2)), T(-2));
    TTS_EQUAL(eve::div[eve::to_nearest](T(3), T(-2)), T(-2));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(3), T(-2)), T(-2));
    TTS_EQUAL(eve::div[eve::to_nearest](v_t(3), v_t(-2)), v_t(-2));
  }

  TTS_EQUAL(eve::div[eve::to_nearest](T(12), T(4)), T(3));
  TTS_EQUAL(eve::div[eve::to_nearest](T(2), T(2)), T(1));
  TTS_EQUAL(eve::div[eve::to_nearest](T(1), T(2)), T(0));
  TTS_EQUAL(eve::div[eve::to_nearest](T(3), T(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](T(5), T(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](T(4), T(3)), T(1));

  TTS_EQUAL(eve::div[eve::to_nearest](v_t(12), T(4)), T(3));
  TTS_EQUAL(eve::div[eve::to_nearest](v_t(1), T(2)), T(0));
  TTS_EQUAL(eve::div[eve::to_nearest](v_t(3), T(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](v_t(5), T(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](v_t(4), T(3)), T(1));

  TTS_EQUAL(eve::div[eve::to_nearest](T(12), v_t(4)), T(3));
  TTS_EQUAL(eve::div[eve::to_nearest](T(1), v_t(2)), T(0));
  TTS_EQUAL(eve::div[eve::to_nearest](T(3), v_t(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](T(5), v_t(2)), T(2));
  TTS_EQUAL(eve::div[eve::to_nearest](T(4), v_t(3)), T(1));
};

//==================================================================================================
//==  conditional div tests on simd
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T> const&)
                          { return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; });

TTS_CASE_WITH("Check behavior of div on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(mini, 127),
                            tts::randoms(mini, 127),
                            tts::randoms(mini, 127)))
<typename T>(T a0, T a1, T a2)
{
  using eve::div;
  using eve::lower;
  using eve::is_nez;
  using eve::to_nearest;
  using eve::upper;
  using eve::detail::map;
  TTS_ULP_EQUAL(div[lower][is_nez(a2)](a0, a2),
                map([](auto e, auto f) { return is_nez(f) ? div[lower](e, f) : e; }, a0, a2),
                2.5);
  TTS_ULP_EQUAL(div[upper][is_nez(a2)](a0, a2),
                map([](auto e, auto f) { return is_nez(f) ? div[upper](e, f) : e; }, a0, a2),
                2.5);
  TTS_ULP_EQUAL(div[to_nearest][is_nez(a2)](a0, a2),
                map([](auto e, auto f) { return is_nez(f) ? div[to_nearest](e, f) : e; }, a0, a2),
                2.5);

  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_EQUAL(div[lower][a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) { return g > 64 ? div[lower](e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(div[upper][a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) { return g > 64 ? div[upper](e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(div[to_nearest][a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) { return g > 64 ? div[to_nearest](e, f) : e; }, a0, a1, a2));
};
