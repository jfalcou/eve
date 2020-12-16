//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minus.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>

TTS_CASE_TPL("Check eve::minus return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::minus(T(0)), T);
}

TTS_CASE_TPL("Check eve::minus behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::minus(T( 1)) , static_cast<T>(-1));
  TTS_EQUAL(eve::minus(T(-1)) , static_cast<T>( 1));
  if (eve::floating_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::minus(T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::minus(T(-0.)))));
  }

}
