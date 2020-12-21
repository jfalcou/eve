//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/nthroot.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(nthroot) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::nthroot)(T(), int()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::nthroot) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::nthroot)(T{8},T{3}), T(2.0/24));
    TTS_EQUAL(eve::derivative_1st(eve::nthroot)(T{16},T{4}), T(2.0/64));
  }
}
