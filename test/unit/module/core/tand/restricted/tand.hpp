//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tand.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::tand) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::tand)(T()), (T));
}

TTS_CASE_TPL("Check eve::restricted_(eve::tand) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  auto ref_tand = [](auto e) { return eve::tanpi(double(e) / 180); };

  TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(T( 0 )) , T(0) );
  TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(T(-0.)) , T(0) );

  TTS_ULP_EQUAL(eve::restricted_(eve::tand)( T(  1)) , T(ref_tand(1.0))        , 3 );
  TTS_ULP_EQUAL(eve::restricted_(eve::tand)(-T(  1)) , T(ref_tand(-1.0))       , 3 );
  TTS_ULP_EQUAL(eve::restricted_(eve::tand)( T( 45)) , T(ref_tand(v_t(45.0)))  , 3 );
  TTS_ULP_EQUAL(eve::restricted_(eve::tand)(-T( 45)) , T(ref_tand(-v_t(45.0))) , 3 );
}
