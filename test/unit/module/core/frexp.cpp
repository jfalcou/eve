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
TTS_CASE_TPL("Check return types of eve::frexp(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::frexp(T()), (eve::wide<kumi::tuple<v_t,v_t>, typename T::cardinal_type>));
  TTS_EXPR_IS(eve::frexp(v_t()), (kumi::tuple<v_t, v_t>));
  TTS_EXPR_IS(eve::frexp[eve::pedantic](T()), (eve::wide<kumi::tuple<v_t,v_t>, typename T::cardinal_type>));
  TTS_EXPR_IS(eve::frexp[eve::pedantic](v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// Tests for eve::frexp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::frexp(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  {
    auto [x, n] = eve::frexp(a0);
    TTS_EQUAL(x,
              tts::map(
                  [](auto e) -> v_t
                  {
                    int ee;
                    return std::frexp(e, &ee);
                  },
                  a0));
    TTS_EQUAL(n,
              tts::map(
                  [](auto e) -> v_t
                  {
                    int ee;
                    std::frexp(e, &ee);
                    return v_t(ee);
                  },
                  a0));
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](a0);
    TTS_EQUAL(x,
              tts::map(
                  [](auto e) -> v_t
                  {
                    int ee;
                    return std::frexp(e, &ee);
                  },
                  a0));
    TTS_EQUAL(n,
              tts::map(
                  [](auto e) -> v_t
                  {
                    int ee;
                    std::frexp(e, &ee);
                    return v_t(ee);
                  },
                  a0));
  }
};

//==================================================================================================
// Test for corner-cases values pedantic !
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::frexp[eve::pedantic] variants on wide",
             eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.nan);
    TTS_IEEE_EQUAL(x, cases.nan);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.inf);
    TTS_EQUAL(x, cases.inf);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp(cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.mzero);
    TTS_EQUAL(x, cases.mzero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.minf);
    TTS_EQUAL(x, cases.minf);
    TTS_EQUAL(n, cases.zero);
  }

  if constexpr( eve::platform::supports_denormals )
  {
    using v_t = eve::element_type_t<T>;
    auto [x, n] = eve::frexp[eve::pedantic](cases.mindenormal);
    TTS_EQUAL(x, eve::half(eve::as<T>()));

    if constexpr( std::is_same_v<v_t, float> ) TTS_EQUAL(n, T(-150) + 2);
    else if constexpr( std::is_same_v<v_t, double> ) TTS_EQUAL(n, T(-1075) + 2);
  }
};
