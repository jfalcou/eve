//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ULP_HPP
#define ULP_HPP


#include <eve/function/ulp.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check ulp return type",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t = eve::wide<Type, T>; 
  TTS_EXPR_IS(eve::ulp(t_t()), t_t);
}

using eve::fixed;

TTS_CASE_TPL("Check eve::ulp behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using t_t = eve::wide<Type, T>; 
  using eve::ulp;
  if constexpr(std::is_floating_point_v<Type>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(ulp(eve::Inf<t_t>()), eve::Nan<t_t>());
      TTS_IEEE_EQUAL(ulp(eve::Minf<t_t>()), eve::Nan<t_t>());
      TTS_IEEE_EQUAL(ulp(eve::Nan<t_t>()), eve::Nan<t_t>());
    }
    TTS_EQUAL(ulp(eve::Mone<t_t>()), eve::Eps<t_t>()/2);
    TTS_EQUAL(ulp(eve::One<t_t>()), eve::Eps<t_t>()/2);
    TTS_EQUAL(ulp(eve::Zero<t_t>()), eve::Mindenormal<t_t>());
  }
  else
  {
    TTS_EQUAL(ulp(eve::Mone<t_t>()), eve::One<t_t>());
    TTS_EQUAL(ulp(eve::One<t_t>()), eve::One<t_t>());
    TTS_EQUAL(ulp(eve::Zero<t_t>()), eve::One<t_t>());
  }
} 

#endif
