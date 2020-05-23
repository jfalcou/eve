//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/eps.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::eps return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::eps(T(0)), T);
}

TTS_CASE_TPL("Check eve::eps behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL( eve::eps(eve::Inf<T>() ), eve::Nan<T>() );
      TTS_IEEE_EQUAL( eve::eps(eve::Minf<T>()), eve::Nan<T>() );
      TTS_IEEE_EQUAL( eve::eps(eve::Nan<T>() ), eve::Nan<T>() );
    }

    TTS_EQUAL( eve::eps(T(-1)), eve::Eps<T>());
    TTS_EQUAL( eve::eps(T( 1)), eve::Eps<T>());

    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL(eve::eps(T(0)), (eve::Mindenormal<T>()));
    }
  }
  else
  {
    TTS_EQUAL(eve::eps(T(-1)), T(1));
    TTS_EQUAL(eve::eps(T( 1)), T(1));
    TTS_EQUAL(eve::eps(T( 0)), T(1));
  }
}
