//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/combinatorial.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::prime_ceil", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::wide<float, eve::cardinal_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::prime_ceil(T()), T);
  TTS_EXPR_IS(eve::prime_ceil(v_t()), v_t);
  TTS_EXPR_IS(eve::float32(eve::prime_ceil)(T()), f_t);
  TTS_EXPR_IS(eve::float32(eve::prime_ceil)(v_t()), float);
  TTS_EXPR_IS(eve::float64(eve::prime_ceil)(T()), d_t);
  TTS_EXPR_IS(eve::float64(eve::prime_ceil)(v_t()), double);
};

//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
TTS_CASE_WITH("Check corner-cases behavior of eve::prime_ceil on wide",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(0, 100))

)
<typename T>(T)
{
  using eve::as;
  using eve::dec;
  using eve::inc;
  using v_t = eve::element_type_t<T>;
  using f_t = eve::wide<float, eve::cardinal_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::prime_ceil(T(0)), T(2));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_ceil)(T(0)), f_t(2));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_ceil)(T(0)), d_t(2));
  TTS_EQUAL(eve::prime_ceil(v_t(0)), v_t(2));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_ceil)(v_t(0)), 2.0f);
  TTS_IEEE_EQUAL(eve::float64(eve::prime_ceil)(v_t(0)), 2.0);

  TTS_EQUAL(eve::prime_ceil(T(1)), T(2));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_ceil)(T(1)), f_t(2));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_ceil)(T(1)), d_t(2));
  TTS_EQUAL(eve::prime_ceil(v_t(1)), v_t(2));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_ceil)(v_t(1)), 2.0f);
  TTS_IEEE_EQUAL(eve::float64(eve::prime_ceil)(v_t(1)), 2.0);
  TTS_EQUAL(eve::prime_ceil(T(4)), T(5));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(T(4)), f_t(5));
  TTS_EQUAL(eve::float64(eve::prime_ceil)(T(4)), d_t(5));
  TTS_EQUAL(eve::prime_ceil(v_t(4)), v_t(5));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(v_t(4)), 5.0f);
  TTS_EQUAL(eve::float64(eve::prime_ceil)(v_t(4)), 5.0);

  auto constexpr maxi = (sizeof(v_t) == 1) ? (52u) : ((sizeof(v_t) == 2) ? (6540u) : (9999u));
  auto np             = eve::nth_prime(dec(maxi));
  auto npp            = eve::nth_prime(maxi);
  TTS_EQUAL(eve::prime_ceil(T(inc(np))), T(npp));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(T(inc(np))), f_t(npp));
  TTS_EQUAL(eve::float64(eve::prime_ceil)(T(inc(np))), d_t(npp));
  TTS_EQUAL(eve::prime_ceil(v_t(inc(np))), v_t(npp));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(v_t(inc(np))), float(npp));
  TTS_EQUAL(eve::float64(eve::prime_ceil)(v_t(inc(np))), double(npp));

  TTS_EQUAL(eve::prime_ceil(T(npp)), T(npp));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(T(npp)), f_t(npp));
  TTS_EQUAL(eve::float64(eve::prime_ceil)(T(npp)), d_t(npp));
  TTS_EQUAL(eve::prime_ceil(v_t(npp)), v_t(npp));
  TTS_EQUAL(eve::float32(eve::prime_ceil)(v_t(npp)), float(npp));
  TTS_EQUAL(eve::float64(eve::prime_ceil)(v_t(npp)), double(npp));
};
