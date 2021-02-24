//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/is_flint.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check eve::is_flint return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_flint(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_flint behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::pedantic(eve::is_flint)(T(1)), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::pedantic(eve::is_flint)(T(2)), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::pedantic(eve::is_flint)(T(1) / T(2)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::pedantic(eve::is_flint)(eve::maxflint(eve::as<T>())),  eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::pedantic(eve::is_flint)(eve::maxflint(eve::as<T>())*2), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::pedantic(eve::is_flint)(eve::valmax(eve::as<T>())/2), eve::false_(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::pedantic(eve::is_flint)(T(1)), eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::pedantic(eve::is_flint)(T(2)), eve::false_(eve::as<T>()) );
  }


}
