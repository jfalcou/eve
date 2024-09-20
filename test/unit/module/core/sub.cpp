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
  TTS_EXPR_IS(eve::sub[eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::sub[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::logical<v_t>()](v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated][eve::logical<v_t>()](v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::sub(T(), T(), T()), T);
  TTS_EXPR_IS(eve::sub(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::sub(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub(v_t(), v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::sub[eve::saturated](T(), T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sub[eve::saturated](v_t(), v_t(), v_t()), v_t);
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
  using eve::lower;
  using eve::upper;
  using eve::sub;
  using eve::detail::map;

  TTS_EQUAL(sub(a0, a2), map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL(sub[saturated](a0, a2),
            map([&](auto e, auto f) { return sub[saturated](e, f); }, a0, a2));
  TTS_EQUAL(sub(a0, a1, a2),
            map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(sub[saturated](a0, a1, a2),
            map([&](auto e, auto f, auto g) { return sub[saturated](sub[saturated](e, f), g); },
                a0,a1,a2)
            );
  TTS_EQUAL(sub(kumi::tuple{a0, a2}), map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL(sub[saturated](kumi::tuple{a0, a2}),
            map([&](auto e, auto f) { return sub[saturated](e, f); }, a0, a2));
  TTS_EQUAL(sub(kumi::tuple{a0, a1, a2}),
            map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(sub[saturated](kumi::tuple{a0, a1, a2}),
            map([&](auto e, auto f, auto g) { return sub[saturated](sub[saturated](e, f), g); },
                a0,a1,a2)
            );
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( sub[lower](kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return sub[lower](sub[lower](e, f), g); }, a0, a1, a2), 1.0);
    TTS_ULP_EQUAL( sub[upper](kumi::tuple{a0, a1, a2}), map([&](auto e, auto f, auto g) { return sub[upper](sub[upper](e, f), g); }, a0, a1, a2), 1.0);
    TTS_EXPECT(eve::all(sub[upper](a0, a1, a2) >=  sub[lower](a0, a1, a2)));
    T w0(1);
    T w1(eve::smallestposval(eve::as<T>()));
    TTS_EXPECT(eve::all(sub[upper](w0, -1) >=  sub(w0, -w1)));
    TTS_EXPECT(eve::all(sub[lower](w0, w1) <= sub(w0, w1)));
  }
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

  auto e0 = a2.get(0);

  TTS_EQUAL(sub[e0 > T(64)](a0, a1),
            map([e0](auto e, auto f) { return e0 > 64 ? sub(e, f) : e; }, a0, a1));
  TTS_EQUAL(sub[a2 > T(64)](a0, a1),
            map([](auto e, auto f, auto g) { return g > 64 ? sub(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(sub[saturated][a2 > T(64)](a0, a1)
           , map([](auto e, auto f, auto g) { return g > 64 ? sub[saturated](e, f) : e; }, a0, a1, a2));
};

/// TODO waiting for interface simplifications to sub scalar tests


//==================================================================================================
// Tests for masked sub
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sub)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sub[mask](a0, a1),
            eve::if_else(mask, eve::sub(a0, a1), a0));
};
