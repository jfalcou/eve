//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ceil.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check bit_ceil return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_ceil(T()), T);
}

TTS_CASE_TPL("Check eve::bit_ceil behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(!eve::floating_value<T>)
  {
    for(v_t z = 4; z < eve::valmax(eve::as<v_t>())/4; z*=2)
    {
      TTS_EQUAL(eve::bit_ceil(T(z))    , T(z));
      TTS_EQUAL(eve::bit_ceil(T(z-1))  , T(z));
      TTS_EQUAL(eve::bit_ceil(T(z/2+1)), T(z));
    }
  }
  else
  {
    TTS_EQUAL(eve::bit_ceil(T(0))  , T(1));
    TTS_EQUAL(eve::bit_ceil(T(1))  , T(1));
    TTS_EQUAL(eve::bit_ceil(T(1.3)), T(2));
    TTS_EQUAL(eve::bit_ceil(T(1.5)), T(2));
    TTS_EQUAL(eve::bit_ceil(T(1.6)), T(2));
    TTS_EQUAL(eve::bit_ceil(T(2.9)), T(4));
  }
}
