//==================================================================================================
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
TTS_CASE_TPL("Check return types of add", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::raw;
  using eve::dekker_prod;

  // regular
  TTS_EXPR_IS(dekker_prod(T(), T()), (kumi::tuple<T, T>));
  TTS_EXPR_IS(dekker_prod(T(), v_t()), (kumi::tuple<T, T>));
  TTS_EXPR_IS(dekker_prod(v_t(), T()), (kumi::tuple<T, T>));
  TTS_EXPR_IS(dekker_prod(v_t(), v_t()), (kumi::tuple<v_t, v_t>));
};

auto mi = tts::constant(
  []<typename T>(eve::as<T> const& tgt)
  { return -2*eve::eps(tgt); });

auto ma = tts::constant(
  []<typename T>(eve::as<T> const& tgt)
  { return 2*eve::eps(tgt); });

//==================================================================================================
//==  dekker_prod simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of dekker_prod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mi, ma),
                            tts::randoms(mi, ma))
             )
  <typename T>(T a0, T a1)
{
  using eve::dekker_prod;
  using eve::as;
  using eve::raw;
  a0 = eve::inc(a0);
  a1 = eve::inc(a1);
  auto [s, r]   = eve::dekker_prod(a0, a1);
  auto [s1, r1] = eve::fma_two_prod(a0, a1);
  TTS_EQUAL(s, a0*a1);
  TTS_EQUAL(s1, s);
  TTS_EQUAL(r1, r);

//   std::cout << std::hexfloat << std::endl;
//   std::cout << "a0  " << a0 << std::endl;
//   std::cout << "a1 " << a1<< std::endl;
//   std::cout << "r  " << r << std::endl;
//   std::cout << "rf " << rf<< std::endl;
};
