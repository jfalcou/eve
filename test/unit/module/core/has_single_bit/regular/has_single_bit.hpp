//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/has_single_bit.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::has_single_bit return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::has_single_bit(T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::has_single_bit behavior", EVE_TYPE)
{
  if constexpr(std::is_signed_v<T>)
  {
    TTS_EQUAL(eve::has_single_bit(T(-1)), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::has_single_bit(T(0))                 , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::has_single_bit(T(1))                 , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::has_single_bit(T(3))                 , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::has_single_bit(T(4))                 , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::has_single_bit(eve::Valmax<T>()/2+1) , eve::true_(eve::as<T>())  );
}
