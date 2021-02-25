//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/geommean.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check geommean return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::geommean)(T(), T()), T );
}

TTS_CASE_TPL("Check  eve::geommean behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::pedantic(eve::geommean)(eve::one(eve::as<T>()) ,  eve::one(eve::as<T>())     ) , eve::one(eve::as<T>()), 0   );
  TTS_ULP_EQUAL(eve::pedantic(eve::geommean)(T( 0 )  , T( 0 )   ) , T( 0 ), 0   );
  TTS_ULP_EQUAL(eve::pedantic(eve::geommean)(eve::one(eve::as<T>()) , T(3)             ) , eve::sqrt(T(3)), 0             );
  TTS_ULP_EQUAL(eve::pedantic(eve::geommean)(eve::valmax(eve::as<T>()), eve::valmax(eve::as<T>()) ) , eve::valmax(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::geommean)(eve::mone(eve::as<T>()), eve::mone(eve::as<T>())), eve::nan(eve::as<T>()), 0);
}
