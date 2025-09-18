//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <cmath>

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
  TTS_EXPR_IS(eve::mul[eve::widen](T(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::mul[eve::widen](T(), v_t()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::mul[eve::widen](v_t(), T()), eve::upgrade_t<T>);
  TTS_EXPR_IS(eve::mul[eve::widen](v_t(), v_t()), eve::upgrade_t<v_t>);
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
  using eve::strict;
  TTS_ULP_EQUAL(mul(a0, a2), tts::map([](auto e, auto f) { return mul(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](a0, a2), tts::map([&](auto e, auto f) { return mul[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul(a0, a1, a2), tts::map([&](auto e, auto f, auto g) { return mul(mul(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](a0, a1, a2), tts::map([&](auto e, auto f, auto g) { return mul[saturated](mul[saturated](e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul(kumi::tuple{a0, a2}), tts::map([](auto e, auto f) { return mul(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](kumi::tuple{a0, a2}), tts::map([&](auto e, auto f) { return mul[saturated](e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL(mul(kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return mul(mul(e, f), g); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(mul[saturated](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return mul[saturated](mul[saturated](e, f), g); }, a0, a1, a2), 0.5);
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( mul[lower](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return mul[lower](mul[lower](e, f), g); }, a0, a1, a2), 1.0);
    TTS_ULP_EQUAL( mul[upper](kumi::tuple{a0, a1, a2}), tts::map([&](auto e, auto f, auto g) { return mul[upper](mul[upper](e, f), g); }, a0, a1, a2), 1.0);
    TTS_EXPECT(eve::all(mul[upper](a0, a1, a2) >=  mul[lower](a0, a1, a2)));
    T  w0{0.1};
    T  w1{0.12f};
    TTS_EXPECT(eve::all(mul[upper](w0, w1)  >  mul(w0, w1)));
    TTS_EXPECT(eve::all(mul[lower](w0, -w1) < mul(w0, -w1)));
    TTS_EXPECT(eve::all(mul[strict][upper](w0, w1)  >  mul(w0, w1)));
    TTS_EXPECT(eve::all(mul[strict][lower](w0, -w1) <  mul(w0, -w1)));
    TTS_EXPECT(eve::all(mul[strict][upper](w0, w1)  >= mul[upper](w0, w1)));
    TTS_EXPECT(eve::all(mul[strict][lower](w0, -w1) <= mul[lower](w0, -w1)));
    using v_t =  eve::element_type_t<T>;
    auto t = [](auto p){ return (p == T::size()-1) ? v_t(100) : v_t(5); };
    constexpr auto s = 3*T::size()/2;
    auto tup = kumi::generate<s>(t);
    TTS_ULP_EQUAL(mul(tup), v_t(100)*std::pow(v_t(5), tup.size()), 0.5);
  }

};

TTS_CASE_WITH("Check behavior of mul widen on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::mul;
  using eve::widen;
  using eve::convert;
  using eve::as;

  TTS_ULP_EQUAL(mul[widen](a0, a1), mul(eve::upgrade(a0), eve::upgrade(a1)), 0.5);
  TTS_ULP_EQUAL(mul[widen ](a0, a1, a2), mul(eve::upgrade(a0), eve::upgrade(a1), eve::upgrade(a2)), 0.5);
  TTS_ULP_EQUAL(mul[widen ](kumi::tuple{a0, a1}), mul[widen ](a0, a1), 0.5);
  TTS_ULP_EQUAL(mul[widen ](kumi::tuple{a0, a1, a2}), mul[widen ](a0, a1, a2), 0.5);

};

//==================================================================================================
//==  mul modular tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mul mod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 96),
                            tts::randoms(0, 96))
             )
  <typename T>(T const& ra0, T const& ra1)
{
  using eve::mul;
  using eve::mod;
  auto a0 = eve::floor(ra0);
  auto a1 = eve::floor(ra1);
  using e_t =  eve::element_type_t<T>;
  e_t p = 97;
  TTS_ULP_EQUAL(mul[mod = p](a0, a1), eve::rem(a0*a1, p), 0.5);
};

//==================================================================================================
//==  mul modular tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mul mod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 96),
                            tts::randoms(0, 96))
             )
  <typename T>(T const& ra0, T const& ra1)
{
  using eve::mul;
  using eve::mod;
  auto a0 = eve::floor(ra0);
  auto a1 = eve::floor(ra1);
  using e_t =  eve::element_type_t<T>;
  e_t p = 97;
  auto rem = [p](auto x){
    while (true)
    {
      auto t = x >= p;
      if (eve::none(t)) return x;
      x = eve::sub[t](x, p);
    }
  };
  TTS_ULP_EQUAL(mul[mod = p](a0, a1), rem(a0*a1), 0.5);
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
  TTS_EQUAL(mul[a2 > T(64)](a0, a1),
            tts::map([](auto e, auto f, auto g) { return g > 64 ? mul(e, f) : e; }, a0, a1, a2));
  TTS_EQUAL(
    mul[saturated][a2 > T(64)](a0, a1),
    tts::map([](auto e, auto f, auto g) { return g > 64 ? mul[saturated](e, f) : e; }, a0, a1, a2));
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

TTS_CASE_WITH("Check behavior of mul kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::mul;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(mul[kahan](a0, a1, a2), eve::downgrade(mul[widen](a0, a1, a2)), 0.5);

};
