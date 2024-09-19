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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of mul", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::mul(T(), T()), T);
  TTS_EXPR_IS(eve::mul(T(), v_t()), T);
  TTS_EXPR_IS(eve::mul(v_t(), T()), T);
  TTS_EXPR_IS(eve::mul(v_t(), v_t()), v_t);

  // saturated
  TTS_EXPR_IS(eve::mul[eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::mul[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::logical<v_t>()](v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated][eve::logical<v_t>()](v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::mul(T(), T(), T()), T);
  TTS_EXPR_IS(eve::mul(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::mul(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::mul(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::mul(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::mul(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::mul(v_t(), v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::mul[eve::saturated](T(), T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::mul[eve::saturated](v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> ) {}
};

//==================================================================================================
//==  mul simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mul on wide",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::saturated;
  using eve::lower;
  using eve::upper;
  using eve::detail::map;
  TTS_ULP_EQUAL(mul(a0, a2), map([](auto e, auto f) { return mul(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](a0, a2), map([&](auto e, auto f) { return mul[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul(a0, a1, a2), map([&](auto e, auto f, auto g) { return mul(mul(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](a0, a1, a2), map([&](auto e, auto f, auto g) { return mul[saturated](mul[saturated](e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul(kumi::tuple{a0, a2}), map([](auto e, auto f) { return mul(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](kumi::tuple{a0, a2}), map([&](auto e, auto f) { return mul[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul(kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return mul(mul(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return mul[saturated](mul[saturated](e, f), g); }, a0, a1, a2), 0.5);
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( mul[lower](kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return mul[lower](mul[lower](e, f), g); }, a0, a1, a2), 1.0);
    TTS_ULP_EQUAL( mul[upper](kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return mul[upper](mul[upper](e, f), g); }, a0, a1, a2), 1.0);
    TTS_EXPECT(eve::all(mul[upper](a0, a1, a2) >=  mul[lower](a0, a1, a2)));
    T  w0{0.1};
    T  w1{0.12f};
    TTS_EXPECT(eve::all(mul[upper](w0, w1) >   mul(w0, w1)));
    TTS_EXPECT(eve::all(mul[lower](-w0, -w1) <  mul(w0, w1)));
  }
};

//==================================================================================================
//==  conditional mul tests on simd
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; };

TTS_CASE_WITH("Check behavior of mul on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::saturated;
  using eve::detail::map;
  TTS_EQUAL(mul[a2 > T(64)](a0, a1),
            map([](auto e, auto f, auto g) { return g > 64 ? mul(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(
      mul[saturated][a2 > T(64)](a0, a1),
      map([](auto e, auto f, auto g) { return g > 64 ? mul[saturated](e, f) : e; }, a0, a1, a2));
};


//==================================================================================================
// Tests for masked mul
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::mul)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
 <typename T, typename M>(T const& a0,
                           T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::mul[mask](a0, a1),
                 eve::if_else(mask, eve::mul(a0, a1), a0));
};
