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
TTS_CASE_TPL("Check return types of modf", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::modf(T())  , (eve::wide<kumi::tuple<v_t, v_t>, typename T::cardinal_type>));
  TTS_EXPR_IS(eve::modf(v_t()), (kumi::tuple<v_t, v_t>)           );
};

//==================================================================================================
//== modf  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of modf on real types full range", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  {
    auto [p0, p1] = eve::modf(T(1.5));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  {
    auto [p0, p1] = eve::modf(T(-1.6));
    TTS_ULP_EQUAL(p0, T(-0.6), 0.5);
    TTS_EQUAL(p1, T(-1));
  }
  {
    auto [p0, p1] = eve::modf(eve::inf(eve::as<T>{}));
    TTS_IEEE_EQUAL(p0, eve::nan(eve::as<T>{}));
    TTS_IEEE_EQUAL(p1, eve::inf(eve::as<T>{}));
  }
  {
    auto [p0, p1] = eve::modf(eve::nan(eve::as<T>{}));
    TTS_IEEE_EQUAL(p0, eve::nan(eve::as<T>{}));
    TTS_IEEE_EQUAL(p1, eve::nan(eve::as<T>{}));
  }
  {
    auto [p0, p1] = eve::modf[eve::pedantic](T(1.5));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  {
    auto [p0, p1] = eve::modf[eve::pedantic](T(-1.6));
    TTS_ULP_EQUAL(p0, T(-0.6), 0.5);
    TTS_EQUAL(p1, T(-1));
  }
  {
    auto [p0, p1] = eve::modf[eve::pedantic](eve::inf(eve::as<T>{}));
    TTS_IEEE_EQUAL(p0, eve::zero(eve::as<T>{}));
    TTS_IEEE_EQUAL(p1, eve::inf(eve::as<T>{}));
  }
};

TTS_CASE_TPL("Check behavior of modf on integer types full range", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  {
    auto [p0, p1] = eve::modf(T(15));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, T(15));
  }

  if constexpr(eve::signed_value<T>)
  {
    auto [p0, p1] = eve::modf(T(-16));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, T(-16));
  }

  {
    auto [p0, p1] = eve::modf[eve::pedantic](T(15));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, T(15));
  }

  if constexpr(eve::signed_value<T>)
  {
    auto [p0, p1] = eve::modf[eve::pedantic](T(-16));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, T(-16));
  }
};

TTS_CASE_WITH("Check behavior of eve::modf(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.999999, 1.0))
             )
<typename T>(T const& a0)
{
  auto [f, t] = eve::modf(a0);
  auto [fp, tp] = eve::modf[eve::pedantic2](a0);
  auto [fr, tr] = eve::modf[eve::raw2](a0);
  auto [fa, ta] = eve::modf[eve::almost = 10](a0);
  TTS_IEEE_EQUAL(f, eve::frac(a0));
  TTS_IEEE_EQUAL(t, eve::trunc(a0));
  TTS_IEEE_EQUAL(fp, eve::frac[eve::pedantic2](a0));
  TTS_IEEE_EQUAL(tp, eve::trunc(a0));
  TTS_IEEE_EQUAL(fr, eve::frac[eve::raw2](a0));
  TTS_IEEE_EQUAL(tr, eve::trunc[eve::raw2](a0));
  TTS_IEEE_EQUAL(fa, eve::frac[eve::almost = 10](a0));
  TTS_IEEE_EQUAL(ta, eve::trunc[eve::almost = 10](a0));
};
