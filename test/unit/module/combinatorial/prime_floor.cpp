//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/combinatorial.hpp>

//TOOD CONVERSION
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::prime_floor", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_wide_as_t<float, T>;
  using d_t = eve::as_wide_as_t<double, T>;
  TTS_EXPR_IS(eve::prime_floor(T()), T);
  TTS_EXPR_IS(eve::prime_floor(v_t()), v_t);
  TTS_EXPR_IS(eve::prime_floor(T(), eve::as<float >()), f_t);
  TTS_EXPR_IS(eve::prime_floor(v_t(), eve::as<float >()), float);
  TTS_EXPR_IS(eve::prime_floor(T(), eve::as<double >()), d_t);
  TTS_EXPR_IS(eve::prime_floor(v_t(), eve::as<double >()), double);
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_WITH("Check corner-cases behavior of eve::prime_floor on wide",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(0, 100))

)
<typename T>(T)
{
  using eve::as;
  using eve::dec;
  using eve::inc;
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_wide_as_t<float, T>;
  using d_t = eve::as_wide_as_t<double, T>;
  TTS_EQUAL(eve::prime_floor(T(0)), T(0));
  TTS_IEEE_EQUAL(eve::prime_floor(T(0), eve::as<float >()), eve::nan(as<f_t>()));
  TTS_IEEE_EQUAL(eve::prime_floor(T(0), eve::as<double>()), eve::nan(as<d_t>()));
  TTS_EQUAL(eve::prime_floor(v_t(0)), v_t(0));
  TTS_IEEE_EQUAL(eve::prime_floor(v_t(0), eve::as<float >()), eve::nan(as<float>()));
  TTS_IEEE_EQUAL(eve::prime_floor(v_t(0), eve::as<double>()), eve::nan(as<double>()));

  TTS_EQUAL(eve::prime_floor(T(1)), T(0));
  TTS_IEEE_EQUAL(eve::prime_floor(T(1), eve::as<float >()), eve::nan(as<f_t>()));
  TTS_IEEE_EQUAL(eve::prime_floor(T(1), eve::as<double>()), eve::nan(as<d_t>()));
  TTS_EQUAL(eve::prime_floor(v_t(1)), v_t(0));
  TTS_IEEE_EQUAL(eve::prime_floor(v_t(1), eve::as<float >()), eve::nan(as<float>()));
  TTS_IEEE_EQUAL(eve::prime_floor(v_t(1), eve::as<double>()), eve::nan(as<double>()));

  TTS_EQUAL(eve::prime_floor(T(4)), T(3));
  TTS_EQUAL(eve::prime_floor(T(4), eve::as<float >()), f_t(3));
  TTS_EQUAL(eve::prime_floor(T(4), eve::as<double>()), d_t(3));
  TTS_EQUAL(eve::prime_floor(v_t(4)), v_t(3));
  TTS_EQUAL(eve::prime_floor(v_t(4), eve::as<float >()), 3.0f);
  TTS_EQUAL(eve::prime_floor(v_t(4), eve::as<double>()), 3.0);

  auto constexpr maxi = (sizeof(v_t) == 1) ? (52u) : ((sizeof(v_t) == 2) ? (6540u) : (9999u));
  auto np             = eve::nth_prime(maxi);
  auto npp            = eve::nth_prime(dec(maxi));
  TTS_EQUAL(eve::prime_floor(T(dec(np))), T(npp));
  TTS_EQUAL(eve::prime_floor(T(dec(np)), eve::as<float >()), f_t(npp));
  TTS_EQUAL(eve::prime_floor(T(dec(np)), eve::as<double>()), d_t(npp));
  TTS_EQUAL(eve::prime_floor(v_t(dec(np))), v_t(npp));
  TTS_EQUAL(eve::prime_floor(v_t(dec(np)), eve::as<float >()), float(npp));
  TTS_EQUAL(eve::prime_floor(v_t(dec(np)), eve::as<double>()), double(npp));

  TTS_EQUAL(eve::prime_floor(T(np)), T(np));
  TTS_EQUAL(eve::prime_floor(T(np), eve::as<float >()), f_t(np));
  TTS_EQUAL(eve::prime_floor(T(np), eve::as<double>()), d_t(np));
  TTS_EQUAL(eve::prime_floor(v_t(np)), v_t(np));
  TTS_EQUAL(eve::prime_floor(v_t(np), eve::as<float >()), float(np));
  TTS_EQUAL(eve::prime_floor(v_t(np), eve::as<double>()), double(np));
};
