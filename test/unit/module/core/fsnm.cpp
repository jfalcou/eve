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
TTS_CASE_TPL("Check return types of fsnm", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fsnm(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fsnm(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fsnm(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fsnm(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fsnm(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fsnm(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fsnm(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fsnm(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fsnm(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fsnm(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fsnm(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fsnm(wi_t(), std::int8_t(), int()), wi_t);
    TTS_EXPR_IS(eve::fsnm(wi_t(), int(), int()), wi_t);
  }
};

//==================================================================================================
// fsnm tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fsnm on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fnms;
  using eve::fsnm;
  using eve::detail::map;
  TTS_IEEE_EQUAL(eve::pedantic(fsnm)(-eve::one(eve::as<T>()), a0, a1),
                 eve::pedantic(fnms)(a0, a1, -eve::one(eve::as<T>())));
};

//==================================================================================================
// fsnm promote tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of promote(fsnm) on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1 )
{
  using eve::as;
  using eve::fsnm;
  using eve::promote;
  using eve::detail::map;

  constexpr int N = eve::cardinal_v<T>;
  eve::wide<float, eve::fixed<N>> fa([](auto i,  auto){return float(i)/2; });
  auto r1 = promote(fsnm)(a0, a1, fa);
  using er1_t =  eve::element_type_t<decltype(r1)>;
  auto refr1 = eve::fsnm(eve::convert(a0, eve::as<er1_t>()), eve::convert(a1, eve::as<er1_t>()), eve::convert(fa, eve::as<er1_t>()));
  TTS_ULP_EQUAL(r1,  refr1, 2.0);

  eve::wide<double, eve::fixed<N>> da([](auto i,  auto){return double(i)/3; });
  auto r2 = promote(fsnm)(a0, da, a1);
  using er2_t =  eve::element_type_t<decltype(r2)>;
  auto refr2 = eve::fsnm(eve::convert(a0, eve::as<er2_t>()), eve::convert(da, eve::as<er2_t>()), eve::convert(a1, eve::as<er2_t>()));
  TTS_ULP_EQUAL(r2,  refr2, 0.5);

  eve::wide<int, eve::fixed<N>> ia([](auto i,  auto){return int(i); });
  auto r3 = promote(fsnm)(ia, a0, a1);
  using er3_t =  eve::element_type_t<decltype(r3)>;
  auto refr3 = eve::fsnm(eve::convert(ia, eve::as<er3_t>()), eve::convert(a0, eve::as<er3_t>()), eve::convert(a1, eve::as<er3_t>()));
  TTS_ULP_EQUAL(r3,  refr3, 0.5);

  auto r4 = promote(fsnm)(ia, da, a1);
  using er4_t =  eve::element_type_t<decltype(r4)>;
  auto refr4= eve::fsnm(eve::convert(ia, eve::as<er4_t>()), eve::convert(da, eve::as<er4_t>()), eve::convert(a1, eve::as<er4_t>()));
  TTS_ULP_EQUAL(r4,  refr4, 0.5);
};

//==================================================================================================
//== fsnm full range tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsnm on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fnms;
  using eve::fsnm;
  using eve::detail::map;

  TTS_IEEE_EQUAL(fsnm(a0, a1, a2), fnms(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::pedantic(fsnm)(a0, a1, a2), eve::pedantic(fnms)(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::numeric(fsnm)(a0, a1, a2), eve::pedantic(fnms)(a1, a2, a0));
};

//==================================================================================================
//== fsnm masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsnm on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fsnm;

  TTS_IEEE_EQUAL(fsnm[t](a0, a1, a2), eve::if_else(t, fsnm[t](a0, a1, a2), a0));
};
