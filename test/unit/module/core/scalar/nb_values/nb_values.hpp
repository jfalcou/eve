//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NB_VALUES_HPP
#define NB_VALUES_HPP

#include <eve/function/scalar/nb_values.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/unary_minus.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE("Check eve::nb_values  behavior")
{
  using eve::nb_values; 
  TTS_EXPR_IS( nb_values(Type(), Type()), (eve::detail::as_integer_t<Type, unsigned>));
  using r_t = eve::detail::as_integer_t<Type, unsigned>; 
  if constexpr(std::is_floating_point_v<Type>)
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
  TTS_EQUAL(nb_values(eve::Mone<Type>(), eve::Mone<Type>()), eve::Zero<r_t>());
  TTS_EQUAL(nb_values(eve::One<Type>(), eve::One<Type>()), eve::Zero<r_t>());
  TTS_EQUAL(nb_values(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<r_t>());
  
}

#endif
