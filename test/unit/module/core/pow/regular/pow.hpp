//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check pow_abs return type", EVE_TYPE)
{
  if (eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::pow(T(0), T(0)), T);
  }
  TTS_EXPR_IS(eve::pow(T(0), int(0)), T);
}

TTS_CASE_TPL("pow conformity", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_positive(eve::pow(eve::Minf<T>(), T(-4) ))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::pow(eve::Minf<T>(), T(-3) ))));

    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  T(-1)          ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  T(-1)          ) , eve::Minf<T>());
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  T(-2)          ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  T(-2)          ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  eve::Minf<T>() ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  eve::Minf<T>() ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow(-T(1)          ,  eve::Minf<T>() ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow(-T(1)          ,  eve::Inf<T>()  ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( T(1)          ,  eve::Nan<T>()  ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( eve::Nan<T>() ,  T(0)           ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( eve::Nan<T>() , -T(0)           ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( T(0.5)        ,  eve::Inf<T>()  ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( T(2)          ,  eve::Inf<T>()  ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow( T(0.5)        ,  eve::Minf<T>() ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow( T(2)          ,  eve::Minf<T>() ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow(-T(0.5)        ,  eve::Inf<T>()  ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow(-T(2)          ,  eve::Inf<T>()  ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow(-T(0.5)        ,  eve::Minf<T>() ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow(-T(2)          ,  eve::Minf<T>() ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( eve::Minf<T>(), -T(3)           ) , T(-0.)        );
    TTS_IEEE_EQUAL(eve::pow( eve::Minf<T>(), -T(4)           ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( eve::Inf<T>() ,  T(4)           ) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::pow( eve::Inf<T>() , -T(4)           ) , T( 0 )        );
  }

  TTS_EQUAL(eve::pow(T(2),-3), T(1/8.0));
  TTS_EQUAL(eve::pow(T(2),3) , T(8)    );
  TTS_EQUAL(eve::pow(T(2),3u), T(8)    );
}
