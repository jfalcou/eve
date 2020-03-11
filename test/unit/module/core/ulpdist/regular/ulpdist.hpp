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
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/unary_minus.hpp>
#include <type_traits>

TTS_CASE("Check eve::ulpdist return type")
{
  TTS_EXPR_IS(eve::ulpdist(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::ulpdist behavior")
{
  using eve::ulpdist; 
  TTS_EXPR_IS( (ulpdist(EVE_TYPE(), EVE_TYPE())), (EVE_TYPE));

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL((ulpdist(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>())), (eve::Zero<EVE_TYPE>()));
      TTS_EQUAL((ulpdist(eve::Minf<EVE_TYPE>(), eve::Minf<EVE_TYPE>())), (eve::Zero<EVE_TYPE>()));
      TTS_EQUAL((ulpdist(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>())), (eve::Zero<EVE_TYPE>()));
    }
    
    TTS_EQUAL( (ulpdist(eve::One<EVE_TYPE>(), eve::inc(eve::Eps<EVE_TYPE>())))
             , EVE_TYPE(0.5)
             );
    
    TTS_EQUAL( (ulpdist(eve::One<EVE_TYPE>(), EVE_TYPE(-eve::dec(eve::Eps<EVE_TYPE>()))))
             , EVE_TYPE(1)
             );
    
    TTS_EQUAL( (ulpdist(eve::One<EVE_TYPE>(), EVE_TYPE(-eve::dec(eve::Eps<EVE_TYPE>()/2))))
             , EVE_TYPE(0.5)
             );
  }
  TTS_EQUAL((ulpdist(eve::Mone<EVE_TYPE>(), eve::Mone<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
  TTS_EQUAL((ulpdist(eve::One<EVE_TYPE>(), eve::One<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
  TTS_EQUAL((ulpdist(eve::Zero<EVE_TYPE>(), eve::Zero<EVE_TYPE>())), eve::Zero<EVE_TYPE>());
}
