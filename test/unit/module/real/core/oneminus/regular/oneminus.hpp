//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::oneminus return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::oneminus(T(0)), T);
}

TTS_CASE_TPL("Check eve::oneminus behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::oneminus(T(1)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::oneminus(T(2))              , T(-1));
    TTS_EQUAL(eve::oneminus(static_cast<T>(-2)), T( 3));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::oneminus(T(-0.)) , T(1));
    TTS_EQUAL(eve::oneminus((T(0))) , T(1));
  }
}
