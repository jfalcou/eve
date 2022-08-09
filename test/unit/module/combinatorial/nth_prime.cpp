//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/combinatorial.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::nth_prime", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::nth_prime(T()), T); };

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::nth_prime on wide",
             eve::test::simd::unsigned_integers

)
<typename T>(tts::type<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::nth_prime(T(0)), T(2));
  TTS_EQUAL(eve::nth_prime(T(5)), T(13));
  TTS_EQUAL(eve::nth_prime(T(19)), T(71));
  TTS_EQUAL(eve::nth_prime(T(53)), T(251));

  if constexpr( sizeof(elt_t) >= 2 ) TTS_EQUAL(eve::nth_prime(T(54)), T(257));
  else TTS_EQUAL(eve::nth_prime(T(54)), T(0));

  if constexpr( sizeof(elt_t) == 2 )
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(9000)), r_t(93187));
  }
  else if constexpr( sizeof(elt_t) == 4 )
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(9000)), r_t(93187));
  }
  else if constexpr( sizeof(elt_t) == 8 )
  {
    using r_t = eve::as_floating_point_t<T>;
    TTS_EQUAL(eve::float64(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float64(eve::nth_prime)(T(9000)), r_t(93187));
  }
};
