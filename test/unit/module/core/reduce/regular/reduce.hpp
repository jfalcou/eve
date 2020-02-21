//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce.hpp>
#include <eve/function/rem_pio2.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/any.hpp>
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

TTS_CASE("Check eve::reduce_fast return type")
{
  TTS_EXPR_IS(eve::reduce(Type(0)), (std::tuple<Type, Type, Type>));
}

TTS_CASE("Check eve::eve::reduce_fast behavior")
{
  int i = 0;
  Value fac = std::is_same_v<Value, float>  ? Value(3) : Value(10);
  Value zz = eve::Valmax<Value>(); 
  while (zz !=  eve::Zero<Value>())
  {
    ++i; 
    auto z =  Type(zz);
    Type n0, r0, dr0, n1, r1, dr1; 
    std::tie(n0, r0, dr0) = eve::rem_pio2(z);
    std::tie(n1, r1, dr1) = eve::reduce(z);
    TTS_ULP_EQUAL(r0, r1, 0.5);
    TTS_EQUAL(n0, n1);
    if (eve::any(eve::ulpdist(r0, r1) > 0.5)) {
      std::cout << "r0 " << r0 << std::endl;
      std::cout << "r1 " << r1 << std::endl;
      std::cout << "n0 " << n0 << std::endl;
      std::cout << "n1 " << n1 << std::endl;
      std::cout << "zz " << zz << std::endl;     
      std::cout << "zz " << std::hexfloat << zz << std::defaultfloat << std::endl;
      break;
    }
    zz /= fac;     
  }

}
