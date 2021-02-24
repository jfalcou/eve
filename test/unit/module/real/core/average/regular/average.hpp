//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check average return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::average(T(), T()), T );
}

TTS_CASE_TPL("Check  eve::average behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::average(eve::one(eve::as<T>()) ,  eve::one(eve::as<T>())     ) , eve::one(eve::as<T>())    );
  TTS_EQUAL(eve::average(T( 0 )  , T( 0 )   ) , T( 0 )   );
  TTS_EQUAL(eve::average(eve::one(eve::as<T>()) , T(3)             ) , T(2)             );
  TTS_EQUAL(eve::average(eve::valmax(eve::as<T>()), eve::valmax(eve::as<T>()) ) , eve::valmax(eve::as<T>()) );
  TTS_EQUAL(eve::average(eve::valmin(eve::as<T>()), eve::valmin(eve::as<T>()) ) , eve::valmin(eve::as<T>()) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::average(eve::mone(eve::as<T>()), eve::mone(eve::as<T>())), eve::mone(eve::as<T>()));
  }
}
