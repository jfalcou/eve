//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rempio2.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/any.hpp>
#include <eve/function/all.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/dist.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/constant.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <utility>

TTS_CASE("Check eve::rempio2 return type")
{
  TTS_EXPR_IS(eve::big_(eve::rempio2)(Type(0)), (std::tuple<Type, Type, Type>));
}

TTS_CASE("Check eve::eve::rempio2 behavior")
{

  Type z(eve::detail::Rempio2_limit(eve::big_type(), Value())); 
  int i =  0; 
  while(true)
  {
    ++i; 
    auto [n, xr, dxr] = eve::big_(eve::rempio2)(z);
    auto [n1, xr1, dxr1] = eve::rem_pio2(z);
    TTS_ULP_EQUAL(xr, xr1, 0.5); 
    TTS_EQUAL(n, n1); 
    z/= 3;
    //  break;
    if (i == 600) break; 
  }
}
