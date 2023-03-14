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
TTS_CASE_TPL("Check return types of fms", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fms(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fms(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fms(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fms(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fms(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fms(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fms(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fms(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fms(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fms(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fms(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fms(wi_t(), std::int8_t(), int()), wi_t);
    TTS_EXPR_IS(eve::fms(wi_t(), int(), int()), wi_t);
  }
};

//==================================================================================================
// fms tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fms on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fms;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(fms)(a0, a1, eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::pedantic(fms)(e, f, v_t(1)); }, a0, a1),
      2);
};

//==================================================================================================
// fms full range tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fms on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fms;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  if( eve::all(eve::fms(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(-1))
               == eve::pedantic(eve::fms)(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(1))) )
  {
    TTS_ULP_EQUAL(
        fms((a0), (a1), (a2)),
        map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fms)(e, f, g); }, a0, a1, a2),
        2);
  }
  else
  {
    TTS_ULP_EQUAL(fms((a0), (a1), (a2)),
                  map([&](auto e, auto f, auto g) -> v_t { return e * f - g; }, a0, a1, a2),
                  5);
  }
  TTS_ULP_EQUAL(
      eve::pedantic(fms)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fms)(e, f, g); }, a0, a1, a2),
      2);
  TTS_ULP_EQUAL(
      eve::numeric(fms)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fms)(e, f, g); }, a0, a1, a2),
      2);
};

//==================================================================================================
// fms promote tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of promote(fms) on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1 )
{
  using eve::as;
  using eve::fms;
  using eve::promote;
  using eve::detail::map;

  constexpr int N = eve::cardinal_v<T>;
  eve::wide<float, eve::fixed<N>> fa([](auto i,  auto){return float(i)/2; });
  auto r1 = promote(fms)(a0, a1, fa);
  using er1_t =  eve::element_type_t<decltype(r1)>;
  auto refr1 = eve::fms(eve::convert(a0, eve::as<er1_t>()), eve::convert(a1, eve::as<er1_t>()), eve::convert(fa, eve::as<er1_t>()));
  TTS_ULP_EQUAL(r1,  refr1, 2.0);

  eve::wide<double, eve::fixed<N>> da([](auto i,  auto){return double(i)/3; });
  auto r2 = promote(fms)(a0, da, a1);
  using er2_t =  eve::element_type_t<decltype(r2)>;
  auto refr2 = eve::fms(eve::convert(a0, eve::as<er2_t>()), eve::convert(da, eve::as<er2_t>()), eve::convert(a1, eve::as<er2_t>()));
  TTS_ULP_EQUAL(r2,  refr2, 0.5);

  eve::wide<int, eve::fixed<N>> ia([](auto i,  auto){return int(i); });
  auto r3 = promote(fms)(ia, a0, a1);
  using er3_t =  eve::element_type_t<decltype(r3)>;
  auto refr3 = eve::fms(eve::convert(ia, eve::as<er3_t>()), eve::convert(a0, eve::as<er3_t>()), eve::convert(a1, eve::as<er3_t>()));
  TTS_ULP_EQUAL(r3,  refr3, 0.5);

  auto r4 = promote(fms)(ia, da, a1);
  using er4_t =  eve::element_type_t<decltype(r4)>;
  auto refr4= eve::fms(eve::convert(ia, eve::as<er4_t>()), eve::convert(da, eve::as<er4_t>()), eve::convert(a1, eve::as<er4_t>()));
  TTS_ULP_EQUAL(r4,  refr4, 0.5);
};

//==================================================================================================
// fms masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fms on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fms;

  TTS_IEEE_EQUAL(fms[t](a0, a1, a2), eve::if_else(t, fms[t](a0, a1, a2), a0));
};
