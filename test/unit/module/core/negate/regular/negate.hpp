//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/negate.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::negate return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::negate(T(), T()), T);
}

TTS_CASE_TPL(" negate behaviour", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::negate(eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>());
      TTS_EQUAL(eve::negate(eve::Minf<T>(), eve::Minf<T>()), eve::Inf<T>());
      TTS_ULP_EQUAL((eve::negate(eve::Nan<T>(), eve::Nan<T>())), eve::Nan<T>(), 0);
      TTS_ULP_EQUAL((eve::negate(eve::Nan<T>(), T( 0 ))), eve::Nan<T>(), 0);
      TTS_ULP_EQUAL((eve::negate(T( 0 ), eve::Nan<T>())), eve::Nan<T>(), 0);
      TTS_ULP_EQUAL((eve::negate(eve::Nan<T>(), T( 0 ))), eve::Nan<T>(), 0);
      TTS_ULP_EQUAL((eve::negate(eve::One<T>(), eve::Nan<T>())), eve::Nan<T>(), 0);
      TTS_ULP_EQUAL((eve::negate(eve::Nan<T>(), eve::One<T>())), eve::Nan<T>(), 0);
    }
    TTS_EQUAL((eve::negate(eve::Mone<T>(), eve::Mone<T>())), eve::One<T>());
    TTS_EQUAL((eve::negate(eve::One<T>(), eve::One<T>())), eve::One<T>());
    TTS_EQUAL((eve::negate(T( 0 ), T( 0 ))), T( 0 ));
    TTS_EQUAL((eve::negate(eve::One<T>(), T( 0 ))), T( 0 ));
    TTS_EQUAL((eve::negate(T(2), T(-3))), T(-2));
    TTS_EQUAL((eve::negate(T(2), T(3))), T(2));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::negate(eve::Mone<T>(), eve::Mone<T>()), eve::One<T>());
    TTS_EQUAL(eve::negate(eve::Mone<T>(), eve::One<T>()), eve::Mone<T>());
  }
  TTS_EQUAL(eve::negate(eve::One<T>(), eve::One<T>()), eve::One<T>());
  TTS_EQUAL(eve::negate(T( 0 ), T( 0 )), T( 0 ));
  TTS_EQUAL(eve::negate(eve::One<T>(), T( 0 )), T( 0 ));
}
