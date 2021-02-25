//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logspace_add.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/function/log.hpp>
#include <type_traits>

TTS_CASE_TPL("Check logspace_add return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::logspace_add(T(), T()), T );
}

TTS_CASE_TPL("Check  eve::logspace_add behavior", EVE_TYPE)
{
  using eve::as;
  using eve::logspace_add;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::inf(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::zero(as<T>())), eve::inf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::minf(as<T>()),eve::zero(as<T>())), eve::zero(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::inf(as<T>()),eve::nan (as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::minf(as<T>()),eve::minf(as<T>())), eve::minf(as<T>()), 0);
    TTS_ULP_EQUAL(logspace_add(eve::nan(as<T>()),eve::nan(as<T>())), eve::nan(as<T>()), 0);
  }

  TTS_ULP_EQUAL(logspace_add(eve::mone(as<T>()),eve::mone(as<T>())), eve::mone(as<T>())+eve::log_2(as<T>()), 0);
  TTS_ULP_EQUAL(logspace_add(eve::one(as<T>()),eve::one(as<T>())), eve::one(as<T>())+eve::log_2(as<T>()), 0);
  TTS_ULP_EQUAL(logspace_add(T(2), T(2)), T(2)+eve::log_2(as<T>()), 0);
  TTS_ULP_EQUAL(logspace_add(eve::zero(as<T>()),eve::zero(as<T>())), eve::log_2(as<T>()), 0);

  for(int i=-5; i < 5; ++i)
  {
    for(int j=-5; i < 5; ++i)
    {
      TTS_ULP_EQUAL(logspace_add(eve::log(T(i)), eve::log(T(j))), eve::log(T(i+j)), 0);
    }
  }
}
