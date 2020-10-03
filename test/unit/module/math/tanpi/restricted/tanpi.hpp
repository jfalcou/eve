//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::restricted(eve::tanpi) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::tanpi)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eeve::restricted(eve::tanpi) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_EXPECT( eve::all(eve::is_positive(eve::restricted(eve::tanpi)( EVE_TYPE( 0 ) )) ));
  TTS_EXPECT( eve::all(eve::is_negative(eve::restricted(eve::tanpi)( EVE_TYPE(-0.) )) ));

  TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(EVE_TYPE( 0 )) , EVE_TYPE(0));
  TTS_IEEE_EQUAL(eve::restricted(eve::tanpi)(EVE_TYPE(-0.)) , EVE_TYPE(0));

  TTS_ULP_EQUAL(eve::restricted(eve::tanpi)(EVE_TYPE(0.125)) , EVE_TYPE(0.41421356237309504880168872420969807856967187537695), 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::tanpi)(-EVE_TYPE(0.125)), EVE_TYPE(-0.41421356237309504880168872420969807856967187537695), 0.5);
}
