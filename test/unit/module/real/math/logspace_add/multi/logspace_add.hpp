//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logspace_add.hpp>
#include <eve/function/log.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <type_traits>

TTS_CASE_TPL("Check logspace_add multi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::logspace_add(T(), T(), T()), T );
}

TTS_CASE_TPL("Check  eve::logspace_add behavior", EVE_TYPE)
{
  using eve::as;
  using eve::logspace_add;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::inf(as<T>()),eve::inf(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::zero(as<T>()),eve::inf(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::minf(as<T>()),eve::zero(as<T>()),eve::minf(as<T>())), eve::zero(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::nan (as<T>()),eve::nan (as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::minf(as<T>()),eve::minf(as<T>()),eve::minf(as<T>())), eve::minf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::nan(as<T>()),eve::nan(as<T>()),eve::nan(as<T>())), eve::nan(as<T>()), 0);
  }

   TTS_ULP_EQUAL(logspace_add(eve::mone(as<T>()),eve::mone(as<T>()),eve::mone(as<T>())), eve::mone(as<T>())+eve::log(T(3)), 4);

   TTS_ULP_EQUAL(logspace_add(eve::one(as<T>()),eve::one(as<T>()),eve::one(as<T>())), eve::one(as<T>())+eve::log(T(3)), 0);
   TTS_ULP_EQUAL(logspace_add(T(2), T(2), T(2)), T(2)+eve::log(T(3)), 0);
   TTS_ULP_EQUAL(logspace_add(eve::zero(as<T>()),eve::zero(as<T>()),eve::zero(as<T>())), eve::log(T(3)), 0);

  for(int k=1; k < 5; ++k)
  {
    for(int i=1; i < 5; ++i)
    {
      for(int j=1; i < 5; ++i)
      {
        TTS_ULP_EQUAL(logspace_add(eve::log(T(k)), eve::log(T(i)), eve::log(T(j))), eve::log(T(i+j+k)), 0.5);
        TTS_ULP_EQUAL(logspace_add(-eve::log(T(k)), -eve::log(T(i)), -eve::log(T(j))), eve::log(T(eve::rec(T(i))+eve::rec(T(j))+eve::rec(T(k)))), 1);
                      }
    }
  }
}
