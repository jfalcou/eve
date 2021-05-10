//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/prime_floor.hpp>
#include <eve/function/nth_prime.hpp>
#include <eve/function/converter.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::prime_floor"
              , eve::test::simd::unsigned_integers)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::wide<float, eve::cardinal_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::prime_floor(T())                       , T );
  TTS_EXPR_IS( eve::prime_floor(v_t())                     , v_t );
  TTS_EXPR_IS( eve::float32(eve::prime_floor)(T())         , f_t );
  TTS_EXPR_IS( eve::float32(eve::prime_floor)(v_t())       , float );
  TTS_EXPR_IS( eve::float64(eve::prime_floor)(T())         , d_t );
  TTS_EXPR_IS( eve::float64(eve::prime_floor)(v_t())       , double );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::prime_floor on wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(0, 100))

         )
<typename T>(T)
{
  using eve::as;
  using eve::dec;
  using eve::inc;
  using v_t = eve::element_type_t<T>;
  using f_t = eve::wide<float, eve::cardinal_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::prime_floor(T(0)),  T(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(T(0)),  eve::nan(as<f_t>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(T(0)),  eve::nan(as<d_t>()));
  TTS_EQUAL(eve::prime_floor(v_t(0)),  v_t(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(v_t(0)),  eve::nan(as<float>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(v_t(0)),  eve::nan(as<double>()));

  TTS_EQUAL(eve::prime_floor(T(1)),  T(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(T(1)),  eve::nan(as<f_t>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(T(1)),  eve::nan(as<d_t>()));
  TTS_EQUAL(eve::prime_floor(v_t(1)),  v_t(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(v_t(1)),  eve::nan(as<float>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(v_t(1)),  eve::nan(as<double>()));

  TTS_EQUAL(eve::prime_floor(T(4)),  T(3));
  TTS_EQUAL(eve::float32(eve::prime_floor)(T(4)),  f_t(3));
  TTS_EQUAL(eve::float64(eve::prime_floor)(T(4)),  d_t(3));
  TTS_EQUAL(eve::prime_floor(v_t(4)),  v_t(3));
  TTS_EQUAL(eve::float32(eve::prime_floor)(v_t(4)),  3.0f);
  TTS_EQUAL(eve::float64(eve::prime_floor)(v_t(4)),  3.0);

  auto constexpr maxi = (sizeof(v_t) == 1) ? (52u) : ((sizeof(v_t) == 2) ? (6540u) : (9999u));
  auto np = eve::nth_prime(maxi);
  auto npp= eve::nth_prime(dec(maxi));
  TTS_EQUAL(eve::prime_floor(T(dec(np))),  T(npp));
  TTS_EQUAL(eve::float32(eve::prime_floor)(T(dec(np))),  f_t(npp));
  TTS_EQUAL(eve::float64(eve::prime_floor)(T(dec(np))),  d_t(npp));
  TTS_EQUAL(eve::prime_floor(v_t(dec(np))),  v_t(npp));
  TTS_EQUAL(eve::float32(eve::prime_floor)(v_t(dec(np))),  float(npp));
  TTS_EQUAL(eve::float64(eve::prime_floor)(v_t(dec(np))),  double(npp));

  TTS_EQUAL(eve::prime_floor(T(np)),  T(np));
  TTS_EQUAL(eve::float32(eve::prime_floor)(T(np)),  f_t(np));
  TTS_EQUAL(eve::float64(eve::prime_floor)(T(np)),  d_t(np));
  TTS_EQUAL(eve::prime_floor(v_t(np)),  v_t(np));
  TTS_EQUAL(eve::float32(eve::prime_floor)(v_t(np)),  float(np));
  TTS_EQUAL(eve::float64(eve::prime_floor)(v_t(np)),  double(np));
};
