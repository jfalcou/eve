/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of min", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::min(T(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::min(T(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// min tests
//==================================================================================================
TTS_CASE_WITH ( "Check behavior of min on all types full range"
              , eve::test::simd::all_types
              , tts::generate ( tts::randoms(eve::valmin, eve::valmin)
                              , tts::randoms(eve::valmin, eve::valmin)
                              , tts::randoms(eve::valmin, eve::valmin)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::abs;
  using eve::min;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return std::min(std::min(a, b), c); };
  TTS_ULP_EQUAL(min(a0, a1, a2), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(min[eve::pedantic](a0, a1, a2), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(min[eve::numeric](a0, a1, a2), tts::map(m, a0, a1, a2), 2);
  auto t = [](auto p){ return (p == T::size()-1) ? v_t(0) : eve::rem(v_t(p/2), v_t(5)); };
  constexpr auto s = 3*T::size()/2;
  auto tup = kumi::generate<s>(t);
  TTS_ULP_EQUAL(min(tup), v_t(0), 0.5);
};

TTS_CASE_TPL("Check values of min", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::min[eve::pedantic](eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::min[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::min[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::min[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::min[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::min[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::min[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::min[eve::numeric](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::min[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::min[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::min[eve::numeric](T(0), T(-0.)))));
};

TTS_CASE_WITH("Check predicate version of min",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin)))
<typename T>(T const& a0, T const& a1)
{
  TTS_EXPR_IS(eve::min(eve::is_less), std::remove_cvref_t<decltype(eve::min)>);
  TTS_EQUAL(eve::min(eve::is_less)(a0, a1), eve::min(a0, a1));

  TTS_EXPR_IS(eve::min(eve::is_greater), std::remove_cvref_t<decltype(eve::max)>);
  TTS_EQUAL(eve::min(eve::is_greater)(a0, a1), eve::max(a0, a1));

  auto pred = [](auto a, auto b) { return eve::abs(a) < eve::abs(b); };
  TTS_EQUAL(eve::min(pred)(a0, a1), eve::if_else(pred(a1, a0), a1, a0));

  // Check for stability a la Stepanov
  using e_t = eve::element_type_t<T>;
  using w_t = eve::wide<kumi::tuple<e_t, e_t>, eve::cardinal_t<T>>;

  w_t a {[](auto i, auto) { return i % 2 ? i / 2 + 1 : 0; }, [](auto i, auto) { return i + 1; }};

  w_t b {[](auto i, auto) { return i % 2 ? i / 2 : 0; }, [](auto i, auto) { return -(i + 1); }};

  w_t ref {[=](auto i, auto) { return i % 2 ? b.get(i) : a.get(i); }};

  auto less_1st = [](auto pa, auto pb) { return get<0>(pa) < get<0>(pb); };
  TTS_EQUAL(eve::min(less_1st)(a, b), ref);
};


//==================================================================================================
// Tests for masked min
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::min)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,T const& a1,M const& mask)
{
  TTS_IEEE_EQUAL(eve::min[mask](a0, a1), eve::if_else(mask, eve::min(a0, a1), a0));
};
