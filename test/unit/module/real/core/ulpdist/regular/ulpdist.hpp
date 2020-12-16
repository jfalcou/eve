//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ulpdist.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::ulpdist return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::ulpdist(T(0), T(0)), (T));
}

TTS_CASE_TPL("Check eve::ulpdist behavior", EVE_TYPE)
{
  using eve::ulpdist;
  using eve::as;
  TTS_EXPR_IS( ulpdist(T(), T()), T);

  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL ( ulpdist(eve::inf(eve::as<T>()), eve::inf(eve::as<T>()))   , T(0) );
      TTS_EQUAL ( ulpdist(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())) , T(0) );
      TTS_EQUAL ( ulpdist(eve::nan(eve::as<T>()), eve::nan(eve::as<T>()))   , T(0) );
    }

    TTS_EQUAL( ulpdist(T(1), eve::inc(eve::eps(as<T>())))      , T(0.5 ) );
    TTS_EQUAL( ulpdist(T(1), T(-eve::dec(eve::eps(as<T>()))))  , T(1   ) );
    TTS_EQUAL( ulpdist(T(1), T(-eve::dec(eve::eps(as<T>())/2))), T(0.5 ) );
  }

  TTS_EQUAL ( ulpdist(T(-1), T(-1)), T(0) );
  TTS_EQUAL ( ulpdist(T( 1), T( 1)), T(0) );
  TTS_EQUAL ( ulpdist(T( 0), T( 0)), T(0) );
}
