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
TTS_CASE_TPL("Check return types of fma", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fma(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fma(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fma(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fma(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fma(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fma(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fma(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fma(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fma(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fma(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fma(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fma(wi_t(), std::int8_t(), int()), wi_t);
  }
};

//==================================================================================================
//  fma tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fma on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fma;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::pedantic(fma)(e, f, v_t(-1)); }, a0, a1),
      2);
};


//==================================================================================================
// fma tests
//==================================================================================================
TTS_CASE_WITH("Check precision behavior of fma on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fma;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::pedantic(fma)(e, f, v_t(-1)); }, a0, a1),
      2);
};

//==================================================================================================
// fma promote tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of promote(fma) on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1 )
{
  using eve::as;
  using eve::fma;
  using eve::promote;
  using eve::detail::map;

  constexpr int N = eve::cardinal_v<T>;
  eve::wide<float, eve::fixed<N>> fa([](auto i,  auto){return float(i)/2; });
  auto r1 = promote(fma)(a0, a1, fa);
  using er1_t =  eve::element_type_t<decltype(r1)>;
  auto refr1 = eve::fma(eve::convert(a0, eve::as<er1_t>()), eve::convert(a1, eve::as<er1_t>()), eve::convert(fa, eve::as<er1_t>()));
  TTS_ULP_EQUAL(r1,  refr1, 0.5);

  eve::wide<double, eve::fixed<N>> da([](auto i,  auto){return double(i)/3; });
  auto r2 = promote(fma)(a0, a1, da);
  using er2_t =  eve::element_type_t<decltype(r2)>;
  auto refr2 = eve::fma(eve::convert(a0, eve::as<er2_t>()), eve::convert(a1, eve::as<er2_t>()), eve::convert(da, eve::as<er2_t>()));
  TTS_ULP_EQUAL(r2,  refr2, 0.5);

  eve::wide<int, eve::fixed<N>> ia([](auto i,  auto){return int(i); });
  auto r3 = promote(fma)(a0, a1, ia);
  using er3_t =  eve::element_type_t<decltype(r3)>;
  auto refr3 = eve::fma(eve::convert(a0, eve::as<er3_t>()), eve::convert(a1, eve::as<er3_t>()), eve::convert(ia, eve::as<er3_t>()));
  TTS_ULP_EQUAL(r3,  refr3, 0.5);
};

//==================================================================================================
//  fma masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fma on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fma;

  TTS_IEEE_EQUAL(fma[t](a0, a1, a2), eve::if_else(t, fma[t](a0, a1, a2), a0));
};
