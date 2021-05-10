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
#include <eve/function/prime_floor.hpp>
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
EVE_TEST( "Check corner-cases behavior of eve::prime_floor variants on wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(-100.0, 100.0))

         )
<typename T>(T)
{
  using eve::as;
  using v_t = eve::element_type_t<T>;
  using f_t = eve::wide<float, eve::cardinal_t<T>>;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::prime_floor(T(0)),  T(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(T(0)),  eve::nan(as<f_t>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(T(0)),  eve::nan(as<d_t>()));
  TTS_EQUAL(eve::prime_floor(v_t(0)),  v_t(0));
  TTS_IEEE_EQUAL(eve::float32(eve::prime_floor)(v_t(0)),  eve::nan(as<float>()));
  TTS_IEEE_EQUAL(eve::float64(eve::prime_floor)(v_t(0)),  eve::nan(as<double>()));

  TTS_EQUAL(eve::prime_floor(T(4)),  T(3));
  TTS_EQUAL(eve::float32(eve::prime_floor)(T(4)),  f_t(3));
  TTS_EQUAL(eve::float64(eve::prime_floor)(T(4)),  d_t(3));
  TTS_EQUAL(eve::prime_floor(v_t(4)),  v_t(3));
  TTS_EQUAL(eve::float32(eve::prime_floor)(v_t(4)),  3.0f);
  TTS_EQUAL(eve::float64(eve::prime_floor)(v_t(4)),  3.0);

  if constexpr(sizeof(v_t) > 2)
  {
    TTS_EQUAL(eve::prime_floor(T(100728)),  T(100703));
    TTS_EQUAL(eve::float32(eve::prime_floor)(T(100728)),  f_t(100703));
    TTS_EQUAL(eve::float64(eve::prime_floor)(T(100728)),  d_t(100703));
    TTS_EQUAL(eve::prime_floor(v_t(100728)),  v_t(100703));
    TTS_EQUAL(eve::float32(eve::prime_floor)(v_t(100728)),  100703.0f);
    TTS_EQUAL(eve::float64(eve::prime_floor)(v_t(100728)),  100703.0);
  }
};
