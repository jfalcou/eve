//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/copysign.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

TTS_CASE_TPL("Check eve::copysign return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::copysign(T(), T()), T);
  TTS_EXPR_IS(eve::copysign(T(), v_t()), T);
}

TTS_CASE_TPL("Check eve::copysign behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::copysign((T(1.)), T(-0.)), (T(-1.)));
  TTS_EQUAL(eve::copysign((T(1.)), (T(0.))        ), (T(1.)));
  TTS_EQUAL(eve::copysign((T(-1.)), (T(-1.)) ) , (T(-1.)) );
  TTS_EQUAL(eve::copysign((T(-1.)), (T(1.))  ) , (T(1.))  );
  TTS_EQUAL(eve::copysign((T(1.)) , (T(1.))  ) , (T(1.))  );
  TTS_EQUAL(eve::copysign((T(1.)) , (T(-1.)) ) , (T(-1.)) );

  TTS_EQUAL(eve::copysign((T(0.)) , (T(0.))) , (T(0.))  );
  TTS_EQUAL(eve::copysign((T(-1.)), (T(0.))) , (T(1.))  );
  TTS_EQUAL(eve::copysign((T(1.)), (T(1.))), (T(1.)) );
  TTS_EQUAL(eve::copysign((T(1.)), (T(0.))), (T(1.)) );
  TTS_EQUAL(eve::copysign((T(0.)), (T(0.))), (T(0.)) );
}
