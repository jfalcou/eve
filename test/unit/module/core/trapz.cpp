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
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::trapz;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c, auto d) -> v_t { return eve::trapz(a, b, c, d); };
  auto y = kumi::tuple{a0, a1, a2, a3};
  TTS_ULP_EQUAL(trapz((a0), (a1), (a2), (a3)), tts::map(m, a0, a1, a2, a3), 2);
  TTS_ULP_EQUAL(trapz(kumi::tuple{a0, a1, a2, a3}), trapz(y), 5);
  TTS_ULP_EQUAL(trapz(a0, y), a0*trapz(y), 0.5);
  auto f = [](auto x) {return eve::sqr(x); };
  auto x = kumi::generate<8>([](auto p){return v_t(p); });
  std::cout << kumi::map(f, x) << std::endl;
  std::cout << eve::is_product_type<decltype(x)>::value << std::endl;
  std::cout << trapz(x, kumi::map(f, x)) << std::endl;
  std::cout << trapz(f, x)               << std::endl;
//  TTS_ULP_EQUAL(trapz(f, x), trapz(x, kumi::map(f, x)), 0.5);
};



TTS_CASE_WITH("Check behavior of trapz widen on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T const& a0, T const& a1,  T const&a2, T const& a3)
{
  using eve::trapz;
  using eve::widen;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
  {
    TTS_ULP_EQUAL(trapz(a0, a1, a2, a3), eve::downgrade(trapz[widen](a0, a1, a2, a3)), 25);
  }

};
