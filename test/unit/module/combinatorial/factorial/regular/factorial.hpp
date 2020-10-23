//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/factorial.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::factorial return type", EVE_TYPE)
{
  if constexpr(eve::simd_value<T>)
  {
    using r_t = eve::wide<double, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::factorial(T()), r_t);
  }
  else
  {
    TTS_EXPR_IS(eve::factorial(T()), double);
  }
}

TTS_CASE_TPL("Check eve::factorial behavior", EVE_TYPE)
{
  using r_t = std::conditional_t<eve::simd_value<T>
    , eve::wide<double, eve::cardinal_t<T>>
   , double>;
  TTS_EQUAL(eve::factorial(T(10)) , r_t(3628800));
  TTS_EQUAL(eve::factorial(T( 5)) , r_t(120));
  TTS_EQUAL(eve::factorial(T(0))  , r_t(1));
  TTS_EQUAL(eve::factorial(T(1))  , r_t(1));
}
