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
#include <eve/function/nth_prime.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::nth_prime"
              , eve::test::simd::unsigned_integers)
<typename T>(eve::as_<T>)
{
  TTS_EXPR_IS(eve::nth_prime(T()), T); 
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::nth_prime on wide"
        , eve::test::simd::unsigned_integers

         )
  <typename T>(eve::as_<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  
  TTS_EQUAL(eve::nth_prime(T(0)) , T(2));
  TTS_EQUAL(eve::nth_prime(T(5)) , T(13));
  TTS_EQUAL(eve::nth_prime(T(19)), T(71));
  TTS_EQUAL(eve::nth_prime(T(53)), T(251));
  
  if constexpr( sizeof(elt_t) >= 2) TTS_EQUAL(eve::nth_prime(T(54)),  T(257));
  else                              TTS_EQUAL(eve::nth_prime(T(54)),  T(0));
  
  if constexpr( sizeof(elt_t) == 2)
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(9000)), r_t(93187));
  }
  else if constexpr( sizeof(elt_t) == 4)
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(9000)), r_t(93187));
  }
  else if constexpr( sizeof(elt_t) == 8)
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float64(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float64(eve::nth_prime)(T(9000)), r_t(93187));
  }  
};
