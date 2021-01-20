//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logspace_sub.hpp>
#include <eve/function/log.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <type_traits>

TTS_CASE_TPL("Check logspace_sub multi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::logspace_sub(T(), T(), T()), T );
}

TTS_CASE_TPL("Check  eve::logspace_sub behavior", EVE_TYPE)
{
  using eve::as;
  using eve::logspace_sub;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(logspace_sub(eve::inf(as<T>()),eve::minf(as<T>()),eve::minf(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_sub(eve::inf(as<T>()),eve::zero(as<T>()),eve::minf(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_sub(eve::minf(as<T>()),eve::zero(as<T>()),eve::inf(as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_sub(eve::inf(as<T>()),eve::nan (as<T>()),eve::nan (as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_sub(eve::minf(as<T>()),eve::inf(as<T>()),eve::inf(as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_sub(eve::nan(as<T>()),eve::nan(as<T>()),eve::nan(as<T>())), eve::nan(as<T>()), 0);
  }

  TTS_ULP_EQUAL(logspace_sub(T(5),eve::one(as<T>()),eve::one(as<T>())), T(4.962680948652626), 4);
  TTS_ULP_EQUAL(logspace_sub(eve::one(as<T>()),eve::mone(as<T>()),eve::mone(as<T>())),  T(6.843702487933823e-01), 0.5);
  TTS_ULP_EQUAL(logspace_sub(T(4), T(2), T(2)), T(3.684370248793382), 1);

  for(int k=10; k < 15; ++k)
  {
    for(int i=1; i < 5; ++i)
    {
      for(int j=1; i < 5; ++i)
      {
        TTS_ULP_EQUAL(logspace_sub(eve::log(T(k)), eve::log(T(i)), eve::log(T(j))), eve::log(T(k-i-j)), 2);
        TTS_ULP_EQUAL(logspace_sub(-eve::log(T(k)), -eve::log(T(i)), -eve::log(T(j))), eve::log(T(eve::rec(T(k))-eve::rec(T(j))-eve::rec(T(k)))), 1);
                      }
    }
  }
}
