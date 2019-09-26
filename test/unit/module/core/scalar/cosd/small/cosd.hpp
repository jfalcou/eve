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
  TTS_EXPR_IS(eve::small_(eve::cosd)(Type(0)),  Type);
}

TTS_CASE("Check eve::small_(eve::cosd) behavior")
{

#ifndef BOOST_SIMD_NO_INVALIDS
  STF_ULP_EQUAL(eve::small_(eve::cosd)(bs::Inf<Type>()),  bs::Nan<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(bs::Minf<Type>()), bs::Nan<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(bs::Nan<Type>()),  bs::Nan<r_t>(), 0.5);
#endif
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(-180)),       bs::Mone<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(-45)),        bs::Sqrt_2o_2<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(-90)),        bs::Zero<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(180)),        bs::Mone<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(45)),         bs::Sqrt_2o_2<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(T(90)),         bs::Zero<r_t>(), 0.5);
  STF_ULP_EQUAL(eve::small_(eve::cosd)(bs::Zero<Type>()), bs::One<r_t>(), 0.5);
}

#endif
