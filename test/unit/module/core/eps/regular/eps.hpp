//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/eps.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::eps return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::eps(T(0)), T);
}

TTS_CASE_TPL("Check eve::eps behavior", EVE_TYPE)
{
  using eve::eps;
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL((eps(eve::Inf<T>())), (eve::Nan<T>()));
      TTS_IEEE_EQUAL((eps(eve::Minf<T>())), (eve::Nan<T>()));
      TTS_IEEE_EQUAL((eps(eve::Nan<T>())), (eve::Nan<T>()));
    }
    TTS_EQUAL((eps(eve::Mone<T>())), (eve::Eps<T>()));
    TTS_EQUAL((eps(eve::One<T>())) , (eve::Eps<T>()));

    if constexpr(eve::platform::supports_denormals)
    {
      TTS_EQUAL((eps(T{0})), (eve::Mindenormal<T>()));
    }
  }
  else
  {
    TTS_EQUAL((eps(eve::Mone<T>())), (eve::One<T>()));
    TTS_EQUAL((eps(eve::One<T>())), (eve::One<T>()));
    TTS_EQUAL((eps(T( 0 ))),(eve::One<T>()));
  }
}
