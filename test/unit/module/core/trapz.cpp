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
TTS_CASE_TPL("Check return types of trapz", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::trapz(T(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::trapz(T(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::trapz(v_t(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::trapz(T(), T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::trapz(v_t(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::trapz(v_t(), T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::trapz(v_t(), v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// trapz tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of trapz on all types full range",
              eve::test::simd::ieee_reals,
              tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::trapz;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c, auto d) -> v_t { return eve::trapz(a, b, c, d); };
  auto y = kumi::tuple{a0, a1, a2, a3};
  auto prec = tts::prec<T>();
  TTS_RELATIVE_EQUAL(trapz((a0), (a1), (a2), (a3)), tts::map(m, a0, a1, a2, a3), prec);
  TTS_ULP_EQUAL(trapz(kumi::tuple{a0, a1, a2, a3}), trapz(y), 5);
  TTS_ULP_EQUAL(trapz(a0, y), a0*trapz(y), 0.5);
  auto f = [](auto x) {return eve::sqr(x); };
  auto x = kumi::generate<8>([](auto p){return v_t(p); });
  TTS_ULP_EQUAL(trapz(f, x), trapz(x, kumi::map(f, x)), 0.5);
};



TTS_CASE_WITH("Check behavior of trapz widen on wide",
              eve::test::simd::ieee_reals,
              tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100))
<typename T>(T const& a0, T const& a1,  T const&a2, T const& a3)
{
  using eve::trapz;
  using eve::widen;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
  {
    TTS_RELATIVE_EQUAL(trapz(a0, a1, a2, a3),
                       eve::downgrade(trapz[widen](a0, a1, a2, a3)),
                       tts::prec<T>());
  }

};

//==================================================================================================
// A trapezoidal sum cancels when the signs differ, and an ULP of a result that has melted to
// nothing is meaningless. The two cases above keep the domain and measure a relative distance; this
// one keeps the ULP claim on data that cannot cancel.
//==================================================================================================
TTS_CASE_WITH("Check behavior of trapz without cancellation",
              eve::test::simd::ieee_reals,
              tts::randoms(1, 100),
                            tts::randoms(1, 100),
                            tts::randoms(1, 100),
                            tts::randoms(1, 100))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::trapz;
  using eve::widen;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c, auto d) -> v_t { return eve::trapz(a, b, c, d); };
  TTS_ULP_EQUAL(trapz((a0), (a1), (a2), (a3)), tts::map(m, a0, a1, a2, a3), 2);
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(trapz(a0, a1, a2, a3), eve::downgrade(trapz[widen](a0, a1, a2, a3)), 2);
};
