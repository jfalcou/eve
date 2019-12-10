//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem_pio2.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/rem_pio2_medium.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/function/next.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/dist.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <utility>

TTS_CASE("Check eve::rem_pio2 return type")
{
  TTS_EXPR_IS(eve::rem_pio2(Type(0)), (std::tuple<Type, Type, Type>));
}

TTS_CASE("Check eve::eve::rem_pio2 behavior")
{

  Value zz = eve::Valmax<Value>();
  int i = 0; 
  while (zz > 1)
  {
    ++i; 
    auto z =  Type(zz);
    Type n0, r0, dr0, n1, r1, dr1;
    std::tie(n1, r1, dr1) = eve::reduce_large(z);
    std::tie(n0, r0, dr0) = eve::rem_pio2(z);
    
    TTS_ULP_EQUAL(r0, r1, 0.5);
    TTS_EQUAL(n0, n1);
    zz /= 10;     
  }
}

