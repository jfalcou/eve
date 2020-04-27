//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DEGINRAD_HPP
#define DEGINRAD_HPP

#include <eve/function/scalar/deginrad.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/fma.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>
#include <eve/constant/ieee_constant.hpp>

TTS_CASE_TPL("Check deginrad return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::deginrad(T(0)),  T);
}

TTS_CASE_TPL("Check eve::deginrad behavior", EVE_TYPE)
{

#ifndef EVE_SIMD_NO_INVALIDS
  TTS_ULP_EQUAL(eve::deginrad(eve::Inf<T>()), eve::Inf<T>(), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::Minf<T>()), eve::Minf<T>(), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::Nan<T>()), eve::Nan<T>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::deginrad(T( 0 )), T( 0 ), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(eve::One<T>()), T(0.017453292519943295769236907684886), 0.5);
  TTS_ULP_EQUAL(eve::deginrad(T(10)),         T(0.17453292519943295769236907684886), 0.5);
}


#endif
