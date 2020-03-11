//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cosh return type")
{
  TTS_EXPR_IS(eve::cosh(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::cosh behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Inf<EVE_TYPE>()) , (eve::Inf<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Minf<EVE_TYPE>()), (eve::Inf<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::cosh(EVE_TYPE(1)), EVE_TYPE(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(EVE_TYPE(-1)),EVE_TYPE(std::cosh(-1.0)), 0.5);
  EVE_VALUE ovflimit =  eve::Ieee_constant<EVE_VALUE,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384  
  std::array<EVE_VALUE, 14> a = {EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(0), EVE_VALUE(-0.0), EVE_VALUE(10), EVE_VALUE(-10)
                             , eve::Maxlog<EVE_VALUE>(), ovflimit/2, ovflimit, 2*ovflimit,
                               -eve::Maxlog<EVE_VALUE>(), -ovflimit/2, -ovflimit, -2*ovflimit };
  
  for(size_t i=0; i < a.size(); ++i)
  {
    auto ch  = eve::cosh(EVE_TYPE(a[i]));
    EVE_VALUE ch1 = std::cosh(double(a[i]));
    TTS_ULP_EQUAL(ch, (EVE_TYPE(ch1)), 0.5);
  }
}
