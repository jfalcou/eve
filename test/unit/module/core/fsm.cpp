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
TTS_CASE_TPL("Check return types of fsm", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fsm(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fsm(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fsm(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fsm(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fsm(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fsm(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fsm(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fsm(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fsm(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fsm(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fsm(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fsm(wi_t(), std::int8_t(), int()), wi_t);
  }
};

//==================================================================================================
//==  fsm tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fsm on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fsm;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::fsm[eve::pedantic](a0, a1, -eve::one(eve::as<T>())),
      tts::map([&](auto e, auto f) -> v_t { return eve::fsm[eve::pedantic](e, f, v_t(-1)); }, a0, a1),
      2);
};


//==================================================================================================
//== fsm tests
//==================================================================================================
TTS_CASE_WITH("Check precision behavior of fsm on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fsm;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::fsm[eve::pedantic](a0, a1, -eve::one(eve::as<T>())),
      tts::map([&](auto e, auto f) -> v_t { return eve::fsm[eve::pedantic](e, f, v_t(-1)); }, a0, a1),
      2);
};

//==================================================================================================
//== fsm upper lower tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsm lower upper on all types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000))
             )
  <typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::as;
  using eve::fsm;
  using eve::lower;
  using eve::upper;
  using eve::strict;
  TTS_EXPECT(eve::all(fsm[upper](a0, a1, a2) >= fsm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsm[lower](a0, a1, a2) <= fsm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsm[upper][strict](a0, a1, a2) > fsm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsm[lower][strict](a0, a1, a2) < fsm(a0, a1, a2)));
  TTS_EXPECT(eve::all(fsm[strict][upper](a0, a1, a2) >= fsm[upper](a0, a1, a2)));
  TTS_EXPECT(eve::all(fsm[strict][lower](a0, a1, a2) <= fsm[lower](a0, a1, a2)));
};

//==================================================================================================
//==  fsm promote tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fsm[promote] on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1 )
{
  using eve::as;
  using eve::fsm;
  using eve::promote;

  constexpr int N = eve::cardinal_v<T>;
  eve::wide<float, eve::fixed<N>> fa([](auto i,  auto){return float(i)/2; });
  auto r1 = fsm[promote](a0, a1, fa);
  using er1_t =  eve::element_type_t<decltype(r1)>;
  auto refr1 = eve::fsm(eve::convert(a0, eve::as<er1_t>()), eve::convert(a1, eve::as<er1_t>()), eve::convert(fa, eve::as<er1_t>()));
  TTS_ULP_EQUAL(r1,  refr1, 2.0);

  eve::wide<double, eve::fixed<N>> da([](auto i,  auto){return double(i)/3; });
  auto r2 = fsm[promote](a0, da, a1);
  using er2_t =  eve::element_type_t<decltype(r2)>;
  auto refr2 = eve::fsm(eve::convert(a0, eve::as<er2_t>()), eve::convert(da, eve::as<er2_t>()), eve::convert(a1, eve::as<er2_t>()));
  TTS_ULP_EQUAL(r2,  refr2, 0.5);

  eve::wide<int, eve::fixed<N>> ia([](auto i,  auto){return int(i); });
  auto r3 = fsm[promote](ia, a0, a1);
  using er3_t =  eve::element_type_t<decltype(r3)>;
  auto refr3 = eve::fsm(eve::convert(ia, eve::as<er3_t>()), eve::convert(a0, eve::as<er3_t>()), eve::convert(a1, eve::as<er3_t>()));
  TTS_ULP_EQUAL(r3,  refr3, 0.5);

  auto r4 = fsm[promote](ia, da, a1);
  using er4_t =  eve::element_type_t<decltype(r4)>;
  auto refr4= eve::fsm(eve::convert(ia, eve::as<er4_t>()), eve::convert(da, eve::as<er4_t>()), eve::convert(a1, eve::as<er4_t>()));
  TTS_ULP_EQUAL(r4,  refr4, 0.5);
};

//==================================================================================================
//  fsm masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of masked fsm on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(1, 5),
                            tts::randoms(1, 5),
                            tts::randoms(1, 5),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::fsm;
  using eve::if_;
  using eve::lower;
  using eve::strict;

  TTS_ULP_EQUAL(fsm[t](a0, a1, a2), eve::if_else(t, fsm(a0, a1, a2), a0), 0);
  TTS_ULP_EQUAL(fsm[if_(t).else_(100)](a0, a1, a2), eve::if_else(t, fsm(a0, a1, a2), 100), 0);
  TTS_ULP_EQUAL(fsm[eve::ignore_all](a0, a1, a2), a0, 0);
  TTS_ULP_EQUAL(fsm[eve::ignore_all.else_(42)](a0, a1, a2), T{42}, 0);

  TTS_IEEE_EQUAL(fsm[t][lower](a0, a1, a2), eve::if_else(t, fsm[lower](a0, a1, a2), a0));
  TTS_IEEE_EQUAL(fsm[if_(t).else_(100)][lower](a0, a1, a2), eve::if_else(t, fsm[lower](a0, a1, a2), 100));
  TTS_IEEE_EQUAL(fsm[eve::ignore_all][lower](a0, a1, a2), a0);
  TTS_IEEE_EQUAL(fsm[eve::ignore_all.else_(42)][lower](a0, a1, a2), T{42});

  TTS_IEEE_EQUAL(fsm[t][lower][strict](a0, a1, a2), eve::if_else(t, fsm[lower][strict](a0, a1, a2), a0));
  TTS_IEEE_EQUAL(fsm[if_(t).else_(100)][lower][strict](a0, a1, a2), eve::if_else(t, fsm[lower][strict](a0, a1, a2), 100));
  TTS_IEEE_EQUAL(fsm[eve::ignore_all][lower][strict](a0, a1, a2), a0);
  TTS_IEEE_EQUAL(fsm[eve::ignore_all.else_(42)][lower][strict](a0, a1, a2), T{42});
};
