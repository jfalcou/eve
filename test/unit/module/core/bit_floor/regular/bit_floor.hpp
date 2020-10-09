//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_floor.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check bit_floor return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_floor(T()), T);
}

TTS_CASE_TPL("Check eve::bit_floor behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(!eve::floating_value<T>)
  {
    for(v_t z = 2; z < eve::valmax(eve::as<v_t>())/2; z*=2)
    {
      TTS_EQUAL(eve::bit_floor(EVE_TYPE(z)), EVE_TYPE(z));
      TTS_EQUAL(eve::bit_floor(EVE_TYPE(z+1)), EVE_TYPE(z));
      TTS_EQUAL(eve::bit_floor(EVE_TYPE(3*(z/2))), EVE_TYPE(z));
    }
  }
  else
  {
    TTS_EQUAL(eve::bit_floor(T(0))   , T(0));
    TTS_EQUAL(eve::bit_floor(T(1.3)) , T(1));
    TTS_EQUAL(eve::bit_floor(T(1.5)) , T(1));
    TTS_EQUAL(eve::bit_floor(T(1.6)) , T(1));
    TTS_EQUAL(eve::bit_floor(T(2.9)) , T(2));
  }
}
