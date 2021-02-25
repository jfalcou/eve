//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/dec.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::dec) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::dec)(T()), T);
}

TTS_CASE_TPL("Check eve::saturated(eve::dec) behavior", EVE_TYPE)
{
  using eve::saturated;

  TTS_EQUAL(saturated(eve::dec)(eve::valmin(eve::as<T>())), eve::valmin(eve::as<T>()));
  TTS_EQUAL(saturated(eve::dec)(T(1))            , (T( 0)) );
  TTS_EQUAL(saturated(eve::dec)(T(2))            , (T( 1)) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(saturated(eve::dec)(T(0)), T(-1) );
  }
  else
  {
    TTS_EQUAL(saturated(eve::dec)(T(0)), T(0) );
  }
}
