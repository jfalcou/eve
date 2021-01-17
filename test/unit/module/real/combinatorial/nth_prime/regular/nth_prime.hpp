//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nth_prime.hpp>

TTS_CASE_TPL("Check eve::nth_prime return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::nth_prime(T()), T);
}

TTS_CASE_TPL("Check eve::nth_prime behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::nth_prime(T(0)) , T(2));
  TTS_EQUAL(eve::nth_prime(T(5)) , T(13));
  TTS_EQUAL(eve::nth_prime(T(19)), T(71));
  TTS_EQUAL(eve::nth_prime(T(53)), T(251));

  if constexpr( sizeof(elt_t) >= 2) TTS_EQUAL(eve::nth_prime(T(54)),  T(257));
  else                              TTS_EQUAL(eve::nth_prime(T(54)),  T(0));

  if constexpr( sizeof(elt_t) == 4)
  {
    using r_t = eve::detail::as_floating_point_t<T>;
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(1000)), r_t(7927));
    TTS_EQUAL(eve::float32(eve::nth_prime)(T(9000)), r_t(93187));
  }

}
