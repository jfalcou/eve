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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of rem", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // downward
  TTS_EXPR_IS(eve::downward(eve::rem)(T(), T()), T);
  TTS_EXPR_IS(eve::downward(eve::rem)(T(), v_t()), T);
  TTS_EXPR_IS(eve::downward(eve::rem)(v_t(), T()), T);
  TTS_EXPR_IS(eve::downward(eve::rem)(v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::upward(eve::rem)(T(), T()), T);
  TTS_EXPR_IS(eve::upward(eve::rem)(T(), v_t()), T);
  TTS_EXPR_IS(eve::upward(eve::rem)(v_t(), T()), T);
  TTS_EXPR_IS(eve::upward(eve::rem)(v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::to_nearest(eve::rem)(T(), T()), T);
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(T(), v_t()), T);
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(v_t(), T()), T);
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(v_t(), v_t()), v_t);

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
  TTS_EQUAL(downward(rem)(a0, a2),
            map([&](auto e, auto f) { return downward(rem)(e, f); }, a0, a2));
  TTS_EQUAL(upward(rem)(a0, a2), map([&](auto e, auto f) { return upward(rem)(e, f); }, a0, a2));
  TTS_EQUAL(to_nearest(rem)(a0, a2),
            map([&](auto e, auto f) { return to_nearest(rem)(e, f); }, a0, a2));
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
  TTS_EQUAL(downward(eve::rem)(T(-1), T(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(v_t(-1), T(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(T(-1), v_t(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(T(-4), T(3)), T(2));
  TTS_EQUAL(downward(eve::rem)(v_t(-4), T(3)), T(2));
  TTS_EQUAL(downward(eve::rem)(T(-4), v_t(3)), T(2));

  TTS_EQUAL(downward(eve::rem)(T(1), T(-2)), T(-1));
  TTS_EQUAL(downward(eve::rem)(v_t(1), T(-2)), T(-1));
  TTS_EQUAL(downward(eve::rem)(T(1), v_t(-2)), T(-1));
  TTS_EQUAL(downward(eve::rem)(T(4), T(-3)), T(-2));
  TTS_EQUAL(downward(eve::rem)(v_t(4), T(-3)), T(-2));
  TTS_EQUAL(downward(eve::rem)(T(4), v_t(-3)), T(-2));

  TTS_EQUAL(downward(eve::rem)(T {12}, T(4)), T(0));
  TTS_EQUAL(downward(eve::rem)(T(1), T(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(T(4), T(3)), T(1));
  TTS_EQUAL(downward(eve::rem)(T(4), T(4)), T(0));

  TTS_EQUAL(downward(eve::rem)(v_t(12), T(4)), T(0));
  TTS_EQUAL(downward(eve::rem)(v_t(1), T(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(v_t(4), T(3)), T(1));

  TTS_EQUAL(downward(eve::rem)(T(12), v_t(4)), T(0));
  TTS_EQUAL(downward(eve::rem)(T(1), v_t(2)), T(1));
  TTS_EQUAL(downward(eve::rem)(T(4), v_t(3)), T(1));

  // upward
  TTS_EQUAL(eve::upward(eve::rem)(T(-1), T(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(-1), T(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(T(-1), v_t(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(T(-4), T(3)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(-4), T(3)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(T(-4), v_t(3)), T(-1));

  TTS_EQUAL(eve::upward(eve::rem)(T(1), T(-2)), T(1));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(1), T(-2)), T(1));
  TTS_EQUAL(eve::upward(eve::rem)(T(1), v_t(-2)), T(1));
  TTS_EQUAL(eve::upward(eve::rem)(T(4), T(-3)), T(1));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(4), T(-3)), T(1));
  TTS_EQUAL(eve::upward(eve::rem)(T(4), v_t(-3)), T(1));

  TTS_EQUAL(eve::upward(eve::rem)(T {12}, T(4)), T(0));
  TTS_EQUAL(eve::upward(eve::rem)(T(1), T(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(T(4), T(3)), T(-2));

  TTS_EQUAL(eve::upward(eve::rem)(v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(1), T(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(v_t(4), T(3)), T(-2));

  TTS_EQUAL(eve::upward(eve::rem)(T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::upward(eve::rem)(T(1), v_t(2)), T(-1));
  TTS_EQUAL(eve::upward(eve::rem)(T(4), v_t(3)), T(-2));

  // to_nearest
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(-1), T(2)), T(-1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(-1), T(2)), T(-1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(-1), v_t(2)), T(-1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(-4), T(3)), T(-1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(-4), T(3)), T(-1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(-4), v_t(3)), T(-1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(T(1), T(-2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(1), T(-2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(1), v_t(-2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(4), T(-3)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(4), T(-3)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(4), v_t(-3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(T {12}, T(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(1), T(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(4), T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(1), T(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(v_t(4), T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(1), v_t(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T(4), v_t(3)), T(1));
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

  TTS_RELATIVE_EQUAL(
      downward(rem[is_nez(a2)])(a0, a2),
      map([](auto e, auto f) { return is_nez(f) ? downward(rem)(e, f) : e; }, a0, a2),
      4e-4);

  TTS_RELATIVE_EQUAL(upward(rem[is_nez(a2)])(a0, a2),
                     map([](auto e, auto f) { return is_nez(f) ? upward(rem)(e, f) : e; }, a0, a2),
                     4e-4);

  TTS_RELATIVE_EQUAL(
      to_nearest(rem[is_nez(a2)])(a0, a2),
      map([](auto e, auto f) { return is_nez(f) ? to_nearest(rem)(e, f) : e; }, a0, a2),
      4e-4);

  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);

  TTS_RELATIVE_EQUAL(
      downward(rem[a2 > T(64)])(a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? downward(rem)(e, f) : e; }, a0, a1, a2),
      4e-4);

  TTS_RELATIVE_EQUAL(
      upward(rem[a2 > T(64)])(a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? upward(rem)(e, f) : e; }, a0, a1, a2),
      4e-4);

  TTS_RELATIVE_EQUAL(
      to_nearest(rem[a2 > T(64)])(a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? to_nearest(rem)(e, f) : e; }, a0, a1, a2),
      4e-4);
};
