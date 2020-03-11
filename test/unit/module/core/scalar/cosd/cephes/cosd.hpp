//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COSD_HPP
#define COSD_HPP

#include <eve/function/scalar/cosd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/sqrt_2o_2.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check cosd return type")
{
  TTS_EXPR_IS(eve::cephes_(eve::cosd)(EVE_TYPE(0)),  EVE_TYPE);
}

TTS_CASE("Check eve::cephes_(eve::cosd) behavior")
{

#ifndef EVE_NO_INVALIDS 
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Inf<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Minf<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
#endif
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(2*eve::Pi<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(-2*eve::Pi<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(-eve::Pio_2<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(-eve::Pio_4<EVE_TYPE>()), eve::Sqrt_2o_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Pi<EVE_TYPE>()), eve::Mone<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(-eve::Pi<EVE_TYPE>()), eve::Mone<EVE_TYPE>(), 0.5);   
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Pio_2<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Pio_4<EVE_TYPE>()), eve::Sqrt_2o_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(eve::Zero<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(3*eve::Pio_4<EVE_TYPE>()/2), EVE_TYPE(0.3826834323650897717284599840304), 0.5);
  TTS_ULP_EQUAL(eve::cephes_(eve::cosd)(3*eve::Pio_2<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 1.0);
}


#endif
