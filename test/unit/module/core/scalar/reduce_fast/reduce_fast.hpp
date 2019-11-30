//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REDUCE_FAST_HPP
#define REDUCE_FAST_HPP

#include <eve/function/scalar/reduce_fast.hpp>
#include <eve/function/scalar/rem_pio2_medium.hpp>
#include <eve/constant/pi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>


TTS_CASE("Check eve::reduce_fast behavior")
{
  TTS_EQUAL(0, 0);
  if constexpr(sizeof(Type) == 4)
  {
    for(int i=0; i < 60 ; ++i)
    {
      Type x = i*eve::Pi<Type>()/8; 
      auto [n, xr, xrc] = eve::reduce_fast(x);
      auto [n1, xr1, xrc1] = eve::rem_pio2(x); 
      std::cout << " x =  " << x << " -> xr =  " << xr << " quad =  " <<  n <<  std::endl;
      std::cout << " x =  " << x << " -> xr1 =  " << xr1 << " quad1 =  " <<  n1 <<  std::endl;
      TTS_ULP_EQUAL(x, xr, 0.5); 
    }
  }
}

#endif
