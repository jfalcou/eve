//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/signnz.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::signnz return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::signnz(T()), T);
}

TTS_CASE_TPL("Check eve::signnz behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::signnz(T(0)), T(1));
  TTS_EQUAL(eve::signnz(T(2)), T(1));

  if constexpr(eve::signed_value<T>)
  {
    if constexpr(eve::floating_value<T>)
    {
      TTS_EQUAL(eve::signnz(static_cast<T>(-0.0)), T(-1));
      TTS_EQUAL(eve::signnz(eve::nan(eve::as<T>())), T(-1));
      TTS_EQUAL(eve::signnz(-eve::nan(eve::as<T>())), T(1));
    }

    TTS_EQUAL(eve::signnz(static_cast<T>(-2)), T(-1));
  }
}
