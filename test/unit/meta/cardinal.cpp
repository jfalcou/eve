//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/cardinal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for scalar cardinals")
{
  TTS_TYPE_IS( eve::cardinal_t<float> , eve::scalar_cardinal );
  TTS_EQUAL  ( eve::cardinal_v<float>   , 1 );

  TTS_TYPE_IS( eve::cardinal_t<eve::logical<float>> , eve::scalar_cardinal );
  TTS_EQUAL  ( eve::cardinal_v<eve::logical<float>> , 1 );
};

TTS_CASE_TPL( "Check for wide cardinals", eve::test::cardinals)
<typename T>(::tts::type<T>)
{
  TTS_TYPE_IS( (eve::cardinal_t< eve::wide<float, T> >), T        );
  TTS_EQUAL  ( (eve::cardinal_v< eve::wide<float, T> >), T::value );

  TTS_TYPE_IS( (eve::cardinal_t< eve::logical<eve::wide<float, T> >>), T        );
  TTS_EQUAL  ( (eve::cardinal_v< eve::logical<eve::wide<float, T> >>), T::value );
};

TTS_CASE_TPL( "Check for SIMD tuple-like type cardinals", eve::test::cardinals)
<typename T>(::tts::type<T>)
{
  using tuple_t = kumi::tuple<float,double,std::int8_t>;

  TTS_TYPE_IS( (eve::cardinal_t<eve::wide<tuple_t, T>>), T        );
  TTS_EQUAL  ( (eve::cardinal_v<eve::wide<tuple_t, T>>), T::value );
};
