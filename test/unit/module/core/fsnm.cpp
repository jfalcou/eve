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
  }
};

//==================================================================================================
//  fsnm tests
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
  using eve::fsnm;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::fsnm[eve::pedantic](a0, a1, -eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::fsnm[eve::pedantic](e, f, v_t(-1)); }, a0, a1),
      2);
};


//==================================================================================================
// fsnm tests
//==================================================================================================
TTS_CASE_WITH("Check precision behavior of fsnm on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fsnm;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::fsnm[eve::pedantic](a0, a1, -eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::fsnm[eve::pedantic](e, f, v_t(-1)); }, a0, a1),
      2);
};

//==================================================================================================
// fsnm upper lower tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsnm lower upper on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000))
             )
  <typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::as;
  using eve::fsnm;
  using eve::detail::map;
  using eve::lower;
  using eve::upper;
  using eve::strict;
  TTS_EXPECT(eve::all(fsnm[upper](a0, a1, a2) >= fsnm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsnm[lower](a0, a1, a2) <= fsnm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsnm[upper][strict](a0, a1, a2) > fsnm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsnm[lower][strict](a0, a1, a2) < fsnm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsnm[strict][upper](a0, a1, a2) >= fsnm[upper](a0, a1, a2)));
  TTS_EXPECT(eve::all(fsnm[strict][lower](a0, a1, a2) <= fsnm[lower](a0, a1, a2)));
};

//==================================================================================================
// fsnm promote tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsnm[promote] on all types",
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
  auto r1 = fsnm[promote](a0, a1, fa);
  using er1_t =  eve::element_type_t<decltype(r1)>;
  auto refr1 = eve::fsnm(eve::convert(a0, eve::as<er1_t>()), eve::convert(a1, eve::as<er1_t>()), eve::convert(fa, eve::as<er1_t>()));
  TTS_ULP_EQUAL(r1,  refr1, 2.0);

  eve::wide<double, eve::fixed<N>> da([](auto i,  auto){return double(i)/3; });
  auto r2 = fsnm[promote](a0, da, a1);
  using er2_t =  eve::element_type_t<decltype(r2)>;
  auto refr2 = eve::fsnm(eve::convert(a0, eve::as<er2_t>()), eve::convert(da, eve::as<er2_t>()), eve::convert(a1, eve::as<er2_t>()));
  TTS_ULP_EQUAL(r2,  refr2, 0.5);

  eve::wide<int, eve::fixed<N>> ia([](auto i,  auto){return int(i); });
  auto r3 = fsnm[promote](ia, a0, a1);
  using er3_t =  eve::element_type_t<decltype(r3)>;
  auto refr3 = eve::fsnm(eve::convert(ia, eve::as<er3_t>()), eve::convert(a0, eve::as<er3_t>()), eve::convert(a1, eve::as<er3_t>()));
  TTS_ULP_EQUAL(r3,  refr3, 0.5);

  auto r4 = fsnm[promote](ia, da, a1);
  using er4_t =  eve::element_type_t<decltype(r4)>;
  auto refr4= eve::fsnm(eve::convert(ia, eve::as<er4_t>()), eve::convert(da, eve::as<er4_t>()), eve::convert(a1, eve::as<er4_t>()));
  TTS_ULP_EQUAL(r4,  refr4, 0.5);
};

//==================================================================================================
//  fsnm masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of masked fsnm on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(1, 5),
                            tts::randoms(1, 5),
                            tts::randoms(1, 5),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::fsnm;
  using eve::if_;
  using eve::lower;

  TTS_IEEE_EQUAL(fsnm[t](a0, a1, a2), eve::if_else(t, fsnm(a0, a1, a2), a0));
  TTS_IEEE_EQUAL(fsnm[if_(t).else_(100)](a0, a1, a2), eve::if_else(t, fsnm(a0, a1, a2), 100));
  TTS_IEEE_EQUAL(fsnm[eve::ignore_all](a0, a1, a2), a0);
  TTS_IEEE_EQUAL(fsnm[eve::ignore_all.else_(42)](a0, a1, a2), T{42});

  TTS_IEEE_EQUAL(fsnm[t][lower](a0, a1, a2), eve::if_else(t, fsnm[lower](a0, a1, a2), a0));
  TTS_IEEE_EQUAL(fsnm[if_(t).else_(100)][lower](a0, a1, a2), eve::if_else(t, fsnm[lower](a0, a1, a2), 100));
  TTS_IEEE_EQUAL(fsnm[eve::ignore_all][lower](a0, a1, a2), a0);
  TTS_IEEE_EQUAL(fsnm[eve::ignore_all.else_(42)][lower](a0, a1, a2), T{42});
};
