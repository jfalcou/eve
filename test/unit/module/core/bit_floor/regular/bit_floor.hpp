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
      runtime.stream() << "  -- bitceil with z= " << +z << std::endl;
      TTS_EQUAL(eve::bit_floor(T(z)), T(z));
      TTS_EQUAL(eve::bit_floor(T(z+1)), T(z));
      TTS_EQUAL(eve::bit_floor(T(3*(z/2))), T(z));
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

