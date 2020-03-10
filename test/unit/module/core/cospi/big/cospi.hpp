//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/cos_pi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <mpreal.h>

TTS_CASE("Check eve::cospi return type")
{
  TTS_EXPR_IS(eve::cospi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cospi behavior")
{
  using mpfr::mpreal;    
  const int digits = 256;
  mpreal::set_default_prec(mpfr::digits2bits(digits));
  const mpreal pi          =    mpfr::const_pi();
  auto mpfr_cospi =  [ = ](Value e){return (e > 2*eve::Maxflint<Value>()) ? Type(1) : Type(Value(mpfr::cos(pi*mpreal(e)))); }; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(Type(1)), Type(mpfr_cospi(Value(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(Type(-1)),Type(mpfr_cospi(Value(-1.0))), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(Type(0)), (Type(1)));
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Mzero<Type>()), (Type(1)));
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(22.5))), (Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(-Type(22.5))),(Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(100000.0))), Type(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(-100000.0))),Type(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(100000000.0))), Type(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(-100000000.0))),Type(1), 0.5);
}  
 
 
 
