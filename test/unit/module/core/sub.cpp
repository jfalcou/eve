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
  TTS_EXPR_IS(eve::sub[eve::widen](T(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::sub[eve::widen](T(), v_t()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::sub[eve::widen](v_t(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::sub[eve::widen](v_t(), v_t()), eve::upgrade_t<v_t>);};

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
  using eve::strict;
  using eve::sub;

  TTS_EQUAL(sub(a0, a2), tts::map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL(sub[saturated](a0, a2),
            tts::map([&](auto e, auto f) { return sub[saturated](e, f); }, a0, a2));
  TTS_EQUAL(sub(a0, a1, a2),
            tts::map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(sub[saturated](a0, a1, a2),
            tts::map([&](auto e, auto f, auto g) { return sub[saturated](sub[saturated](e, f), g); },
                a0,a1,a2)
            );
  TTS_EQUAL(sub(kumi::tuple{a0, a2}), tts::map([](auto e, auto f) { return sub(e, f); }, a0, a2));
  TTS_EQUAL(sub[saturated](kumi::tuple{a0, a2}),
            tts::map([&](auto e, auto f) { return sub[saturated](e, f); }, a0, a2));
  TTS_EQUAL(sub(kumi::tuple{a0, a1, a2}),
            tts::map([&](auto e, auto f, auto g) { return sub(sub(e, f), g); }, a0, a1, a2));
  TTS_EQUAL(sub[saturated](kumi::tuple{a0, a1, a2}),
            tts::map([&](auto e, auto f, auto g) { return sub[saturated](sub[saturated](e, f), g); },
                a0,a1,a2)
            );
  TTS_IEEE_EQUAL(eve::sub[eve::left](a0, a2), eve::sub(a2, a0));
  TTS_IEEE_EQUAL(eve::sub[eve::left][a0 < 5](a0, a2), eve::if_else(a0 < 5, eve::sub(a2, a0), a0));
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( sub[lower](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return sub[lower](sub[lower](e, f), g); }, a0, a1, a2), 1.0);
    TTS_ULP_EQUAL( sub[upper](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return sub[upper](sub[upper](e, f), g); }, a0, a1, a2), 1.0);
    TTS_EXPECT(eve::all(sub[upper](a0, a1, a2) >=  sub[lower](a0, a1, a2)));
    T w0(1);
    T w1(eve::smallestposval(eve::as<T>()));
    TTS_EXPECT(eve::all(sub[upper](w0, w1)  >= sub(w0, w1)));
    TTS_EXPECT(eve::all(sub[lower](w0, -w1) <= sub(w0, -w1)));
    TTS_EXPECT(eve::all(sub[strict][upper](w0, w1)  >  sub(w0, w1)));
    TTS_EXPECT(eve::all(sub[strict][lower](w0, -w1) <  sub(w0, -w1)));
    TTS_EXPECT(eve::all(sub[strict][upper](w0, w1)  >= sub[upper](w0, w1)));
    TTS_EXPECT(eve::all(sub[strict][lower](w0, -w1) <= sub[lower](w0, -w1)));
  }
};

//==================================================================================================
//==  sub widen tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of sub widen on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::sub;
  using eve::widen;
  using eve::convert;
  using eve::as;

  TTS_ULP_EQUAL(sub[widen](a0, a1), sub(eve::upgrade(a0), eve::upgrade(a1)), 0.5);
  TTS_ULP_EQUAL(sub[widen ](a0, a1, a2), sub(eve::upgrade(a0), eve::upgrade(a1), eve::upgrade(a2)), 0.5);
  TTS_ULP_EQUAL(sub[widen ](kumi::tuple{a0, a1}), sub[widen ](a0, a1), 0.5);
  TTS_ULP_EQUAL(sub[widen ](kumi::tuple{a0, a1, a2}), sub[widen ](a0, a1, a2), 0.5);

};

//==================================================================================================
//==  sub modular tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of sub mod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 96),
                            tts::randoms(0, 96))
             )
  <typename T>(T const& ra0, T const& ra1)
{
  using eve::sub;
  using eve::mod;
  auto a0 = eve::floor(ra0);
  auto a1 = eve::floor(ra1);
  using e_t =  eve::element_type_t<T>;
  e_t p = 97;
  auto z = a0-a1;
  TTS_ULP_EQUAL(sub[mod = p](a0, a1), eve::if_else(z < 0, z+p, z), 0.5);
};

//==================================================================================================
//==  conditional sub tests on simd
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0; };

TTS_CASE_WITH("Check behavior of sub[mask]",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127)))
<typename T>(T const& a0, T const& a1)
{
  using eve::saturated;
  using eve::sub;

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  if constexpr (eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(sub[m](a0, a1), tts::map([](auto e, auto f, auto me) { return me ? sub(e, f) : e; }, a0, a1, m));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::upper][m](a0, a1) >= sub(a0, a1),
              sub[eve::upper][m](a0, a1) == a0)));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::lower][m](a0, -a1) <= sub(a0, -a1),
              sub[eve::lower][m](a0, -a1) == a0)));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::strict][m][eve::upper](a0, a1) > sub(a0, a1),
              sub[eve::strict][m][eve::upper](a0, a1) == a0)));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::strict][m][eve::lower](a0, -a1) < sub(a0, -a1),
              sub[eve::strict][m][eve::lower](a0, -a1) == a0)));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::strict][m][eve::upper](a0, a1) >= sub[eve::upper](a0, a1),
              sub[eve::strict][m][eve::upper](a0, a1) == a0)));

    TTS_EXPECT(eve::all(eve::if_else(m,
              sub[eve::strict][m][eve::lower](a0, -a1) <= sub[eve::lower](a0, -a1),
              sub[eve::strict][m][eve::lower](a0, -a1) == a0)));
  }
  else
  {
    TTS_EQUAL(sub[m](a0, a1), tts::map([](auto e, auto f, auto me) { return me ? sub(e, f) : e; }, a0, a1, m));
    TTS_EQUAL(sub[eve::saturated][m](a0, a1), tts::map([](auto e, auto f, auto me) { return me ? sub[eve::saturated](e, f) : e; }, a0, a1, m));
  }
};
