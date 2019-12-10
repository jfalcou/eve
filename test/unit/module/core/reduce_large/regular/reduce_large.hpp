//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce_large.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/reduce_large.hpp>
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

TTS_CASE("Check eve::reduce_large return type")
{
  TTS_EXPR_IS(eve::reduce_large(Type(0)), (std::tuple<Type, Type, Type>));
}

TTS_CASE("Check eve::eve::sin behavior")
{

  Value z = eve::Valmax<Value>(); 
  int i =  0; 
  while(true)
  {
    auto [n, xr, dxr] = eve::reduce_large(z);
    auto [n1, xr1, dxr1] = eve::rem_pio2(z);
    TTS_ULP_EQUAL(xr, xr1, 0.5); 
    TTS_EQUAL(n, n1); 
    auto k = eve::ulpdist(xr, xr1);
    z/= 3;
    //  break;
    if (i == 300) break; 
    if (eve::all(z < eve::Pio_4<Value>())) break; 
  }
}
