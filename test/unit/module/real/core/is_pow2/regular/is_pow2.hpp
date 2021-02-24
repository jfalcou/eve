//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check eve::is_pow2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_pow2(T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_pow2 behavior", EVE_TYPE)
{
  if constexpr(std::is_signed_v<T>)
  {
    TTS_EQUAL(eve::is_pow2(T(-1)), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_pow2(T(0))                , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_pow2(T(1))                , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_pow2(T(3))                , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_pow2(T(4))                , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_pow2(eve::valmax(eve::as<T>())/2+1), eve::true_(eve::as<T>())  );
}
