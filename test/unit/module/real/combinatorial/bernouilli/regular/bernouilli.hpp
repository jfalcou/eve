//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bernouilli.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bernouilli_b2n return type", EVE_TYPE)
{
  if constexpr(eve::simd_value<T>)
  {
    using r_t = eve::wide<double, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::bernouilli(T()), r_t);
  }
  else
  {
    TTS_EXPR_IS(eve::bernouilli(T()), double);
  }
}

TTS_CASE_TPL("Check eve::bernouilli behavior", EVE_TYPE)
{
  using r_t = std::conditional_t<eve::simd_value<T>
    , eve::wide<double, eve::cardinal_t<T>>
   , double>;
  TTS_EQUAL(eve::bernouilli(T(10)) , r_t(5.0/66));
  TTS_EQUAL(eve::bernouilli(T(4))  , r_t(-1.0/30));
  TTS_EQUAL(eve::bernouilli(T(0))  , r_t(1));
  TTS_EQUAL(eve::bernouilli(T(1))  , r_t(-0.5));
}
