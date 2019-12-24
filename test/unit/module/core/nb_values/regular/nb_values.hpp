//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
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

TTS_CASE("Check eve::nb_values return type")
{
  using r_t = eve::detail::as_integer_t<Type, unsigned>; 
  TTS_EXPR_IS((eve::nb_values(Type(0), Type(0))), (r_t));
}

TTS_CASE("Check eve::nb_values  behavior")
{
  using eve::nb_values; 
  TTS_EXPR_IS( nb_values(Type(), Type()), (eve::detail::as_integer_t<Type, unsigned>));
  using r_t = eve::detail::as_integer_t<Type, unsigned>; 
  if constexpr(std::is_floating_point_v<Value>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(nb_values(eve::Inf<Type>(), eve::Inf<Type>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Minf<Type>(), eve::Minf<Type>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Nan<Type>(), eve::Nan<Type>()), eve::Valmax<r_t>());
    }
    
    TTS_EQUAL( nb_values(eve::One<Type>(), eve::inc(eve::Eps<Type>()))
             , r_t(1)
             );
    
    TTS_EQUAL( nb_values(eve::One<Type>(), Type(-eve::dec(eve::Eps<Type>())))
             , r_t(2)
             );
    
    TTS_EQUAL( nb_values(eve::One<Type>(), Type(-eve::dec(eve::Eps<Type>()/2)))
             , r_t(1)
             );
  }
  else
  {
    TTS_EQUAL((nb_values(eve::One<Type>(), Type(10))), (r_t(9)));
    TTS_EQUAL(nb_values(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<r_t>());
  }
}
