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
  TTS_EXPR_IS(eve::add[eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(eve::add[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated][eve::logical<v_t>()](v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::add(T(), T(), T()), T);
  TTS_EXPR_IS(eve::add(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::add(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::add(int(), std::int8_t(), T()), T);
  TTS_EXPR_IS(eve::add(int(), T(), int()), T);

  TTS_EXPR_IS(eve::add[eve::saturated](T(), T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::add[eve::saturated](v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::add[eve::widen](T(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::add[eve::widen](T(), v_t()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::add[eve::widen](v_t(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::add[eve::widen](v_t(), v_t()), eve::upgrade_t<v_t>);

};

//==================================================================================================
//==  add simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of add on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const& a2)
{
  using eve::add;
  using eve::as;
  using eve::saturated;
  using eve::lower;
  using eve::upper;
  using eve::strict;

  TTS_ULP_EQUAL( add(a0), a0, 0.5); 
  TTS_ULP_EQUAL( add(a0, a2), tts::map([](auto e, auto f) { return add(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( add[saturated](a0, a2), tts::map([&](auto e, auto f) { return add[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( add(a0, a1, a2), tts::map([&](auto e, auto f, auto g) { return add(add(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( add[saturated](a0, a1, a2), tts::map([&](auto e, auto f, auto g) { return add[saturated](add[saturated](e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( add(kumi::tuple{a0, a2}), tts::map([](auto e, auto f) { return add(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( add[saturated](kumi::tuple{a0, a2}), tts::map([&](auto e, auto f) { return add[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( add(kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return add(add(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( add[saturated](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return add[saturated](add[saturated](e, f), g); }, a0, a1, a2), 0.5);
  if constexpr (eve::floating_value<T> && sizeof(eve::element_type_t<T>) == 4)
  {
    TTS_ULP_EQUAL( add[lower](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return add[lower](add[lower](e, f), g); }, a0, a1, a2), 1.0);
    TTS_ULP_EQUAL( add[upper](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return add[upper](add[upper](e, f), g); }, a0, a1, a2), 1.0);
    TTS_EXPECT(eve::all(add[upper](a0, a1, a2) >=  add[lower](a0, a1, a2)));
    T w0(1);
    T w1(eve::smallestposval(eve::as<T>()));
    TTS_EXPECT(eve::all(add[upper](w0, w1)  >  add(w0, w1)));
    TTS_EXPECT(eve::all(add[lower](w0, -w1) < add(w0, -w1)));
    TTS_EXPECT(eve::all(add[upper][strict](w0, w1)  >  add(w0, w1)));
    TTS_EXPECT(eve::all(add[lower][strict](w0, -w1) <  add(w0, -w1)));
    TTS_EXPECT(eve::all(add[strict][upper](w0, w1)  >= add[upper](w0, w1)));
    TTS_EXPECT(eve::all(add[strict][lower](w0, -w1) <= add[lower](w0, -w1)));
    TTS_EXPECT(eve::all(add[lower](w0, w1) <= add[eve::to_nearest_odd](w0, w1)));
    TTS_EXPECT(eve::all(add[upper](w0, w1) >= add[eve::to_nearest_odd](w0, w1)));
  }
};

TTS_CASE_WITH("Check behavior of add widen on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::add;
  using eve::widen;
  using eve::convert;
  using eve::as;

  TTS_ULP_EQUAL(add[widen](a0, a1), add(eve::upgrade(a0), eve::upgrade(a1)), 0.5);
  TTS_ULP_EQUAL(add[widen ](a0, a1, a2), add(eve::upgrade(a0), eve::upgrade(a1), eve::upgrade(a2)), 0.5);
  TTS_ULP_EQUAL(add[widen ](kumi::tuple{a0, a1}), add[widen ](a0, a1), 0.5);
  TTS_ULP_EQUAL(add[widen ](kumi::tuple{a0, a1, a2}), add[widen ](a0, a1, a2), 0.5);

};

//==================================================================================================
//==  add modular tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of add mod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 96),
                            tts::randoms(0, 96))
             )
  <typename T>(T const& ra0, T const& ra1)
{
  using eve::add;
  using eve::mod;
  auto a0 = eve::floor(ra0);
  auto a1 = eve::floor(ra1);
  using e_t =  eve::element_type_t<T>;
  e_t p = 97;
  auto z = a0+a1;
  TTS_ULP_EQUAL(add[mod = p](a0, a1), eve::if_else(z > p, z-p, p), 0.5);
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

  auto e0 = a2.get(0);

  TTS_EQUAL(add[e0 > T(64)](a0, a1),
            tts::map([e0](auto e, auto f) { return e0 > 64 ? add(e, f) : e; }, a0, a1));
  TTS_EQUAL(add[a2 > T(64)](a0, a1),
            tts::map([](auto e, auto f, auto g) { return g > 64 ? add(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(
      add[saturated][a2 > T(64)](a0, a1),
      tts::map([](auto e, auto f, auto g) { return g > 64 ? add[saturated](e, f) : e; }, a0, a1, a2));
};


//==================================================================================================
//== Tests for masked add
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::add)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::add[mask](a0, a1),
            eve::if_else(mask, eve::add(a0, a1), a0));
  TTS_IEEE_EQUAL(eve::add[mask][eve::lower](a0, a1),
                 eve::if_else(mask, eve::add[eve::lower](a0, a1), a0));

  using eve::lower;
  using eve::if_;
  TTS_IEEE_EQUAL(eve::add[mask][lower](a0, a1), eve::if_else(mask, eve::add[lower](a0, a1), a0));
  TTS_IEEE_EQUAL(eve::add[if_(mask).else_(100)][lower](a0, a1), eve::if_else(mask, eve::add[lower](a0, a1), 100));
  TTS_IEEE_EQUAL(eve::add[eve::ignore_all][lower](a0, a1), a0);
  TTS_IEEE_EQUAL(eve::add[eve::ignore_all.else_(42)][lower](a0, a1), T{42});

};


TTS_CASE_WITH("Check behavior of add kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::add;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(add[kahan](a0, a1, a2), eve::downgrade(add[widen](a0, a1, a2)), 0.5);

};
