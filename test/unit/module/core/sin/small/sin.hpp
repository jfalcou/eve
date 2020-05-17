//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::small_(eve::sin) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small_(eve::sin)(T()), T);
}

TTS_CASE_TPL("Check eve::small_(eve::sin) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Minf<T>()), (eve::Nan<T>()) );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::small_(eve::sin)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small_(eve::sin)(T( 0 )))));

  TTS_IEEE_EQUAL(eve::small_(eve::sin)(T( 0 )), T(0));
  TTS_IEEE_EQUAL(eve::small_(eve::sin)(T(-0.)), T(0));

  auto pio2   = eve::Pio_2<T>();
  auto pio4   = eve::Pio_4<T>();
  auto vpio2  = eve::Pio_2<v_t>();
  auto vpio4  = eve::Pio_4<v_t>();

  TTS_ULP_EQUAL(eve::small_(eve::sin)(  T(1)  ) , T(std::sin( 1.0    )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)( -T(1)  ) , T(std::sin(-1.0    )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)( pio2   ) , T(std::sin( vpio2  )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)(-pio2   ) , T(std::sin(-vpio2  )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)( pio4   ) , T(std::sin( vpio4  )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)(-pio4   ) , T(std::sin(-vpio4  )), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)( pio4/2 ) , T(std::sin( vpio4/2)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)(-pio4/2 ) , T(std::sin(-vpio4/2)), 0.5);
}
