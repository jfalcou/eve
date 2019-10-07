//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REDUCE_LARGE_HPP
#define REDUCE_LARGE_HPP

#include <eve/function/scalar/reduce_large.hpp>
#include <eve/function/scalar/rem_pio2.hpp>
#include <eve/constant/pi.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>


TTS_CASE("Check eve::reduce_large behavior")
{
  TTS_EQUAL(0, 0);
    for(int i=0; i < 20000 ; i+= 100)
    {
      Type x = i*i*1.2345; 
      auto [n, xr, dxr] = eve::reduce_large(x);
      auto [n1, xr1] = eve::rem_pio2(x);
      std::cout << std::setprecision(15) << " dxr = " <<  dxr <<  std::endl;
      std::cout << " x =  " << x << " -> xr =  " << xr << " quad =  " <<  n <<  std::endl;
      std::cout << " x =  " << x << " -> xr1 =  " << xr1 << " quad1 =  " <<  n1 <<  std::endl;
      std::cout << " diff " << xr-xr1 << std::endl; 
      TTS_ULP_EQUAL(xr, xr1, 0.5); 
      TTS_EQUAL(n, n1); 
    }

}

#endif
