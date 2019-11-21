//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
//#include <eve/function/next.hpp>
//#include <eve/function/prev.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/unary_minus.hpp>
#include <type_traits>

TTS_CASE("Check eve::ulpdist return type")
{
  TTS_EXPR_IS(eve::ulpdist(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::ulpdist behavior")
{
  using eve::ulpdist; 
  TTS_EXPR_IS( (ulpdist(Type(), Type())), (Type));

  if constexpr(std::is_floating_point_v<Type>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL((ulpdist(eve::Inf<Type>(), eve::Inf<Type>())), (eve::Zero<Type>()));
      TTS_EQUAL((ulpdist(eve::Minf<Type>(), eve::Minf<Type>())), (eve::Zero<Type>()));
      TTS_EQUAL((ulpdist(eve::Nan<Type>(), eve::Nan<Type>())), (eve::Zero<Type>()));
    }
    
    TTS_EQUAL( (ulpdist(eve::One<Type>(), eve::inc(eve::Eps<Type>())))
             , Type(0.5)
             );
    
    TTS_EQUAL( (ulpdist(eve::One<Type>(), Type(-eve::dec(eve::Eps<Type>()))))
             , Type(0.5)
             );
    
    TTS_EQUAL( (ulpdist(eve::One<Type>(), Type(-eve::dec(eve::Eps<Type>()/2))))
             , Type(0.25)
             );
  }
  TTS_EQUAL((ulpdist(eve::Mone<Type>(), eve::Mone<Type>())), eve::Zero<Type>());
  TTS_EQUAL((ulpdist(eve::One<Type>(), eve::One<Type>())), eve::Zero<Type>());
  TTS_EQUAL((ulpdist(eve::Zero<Type>(), eve::Zero<Type>())), eve::Zero<Type>());
}
