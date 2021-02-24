//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/has_single_bit.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

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
  TTS_EQUAL(eve::has_single_bit(eve::valmax(eve::as<T>())/2+1) , eve::true_(eve::as<T>())  );
}
