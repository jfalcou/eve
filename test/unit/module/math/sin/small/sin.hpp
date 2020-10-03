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

TTS_CASE("Check eve::small(eve::sin) return type")
{
  TTS_EXPR_IS(eve::small(eve::sin)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::small(eve::sin) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::sin)(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::small(eve::sin)(eve::inf(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::small(eve::sin)(eve::minf(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::small(eve::sin)(EVE_TYPE(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small(eve::sin)(EVE_TYPE( 0 )))));

  TTS_IEEE_EQUAL(eve::small(eve::sin)(EVE_TYPE( 0 )), EVE_TYPE(0));
  TTS_IEEE_EQUAL(eve::small(eve::sin)(EVE_TYPE(-0.)), EVE_TYPE(0));

  auto pio2   = eve::pio_2(eve::as<EVE_TYPE>());
  auto pio4   = eve::pio_4(eve::as<EVE_TYPE>());
  auto vpio2  = eve::pio_2(eve::as<EVE_VALUE>());
  auto vpio4  = eve::pio_4(eve::as<EVE_VALUE>());

  TTS_ULP_EQUAL(eve::small(eve::sin)(  EVE_TYPE(1)  ) , EVE_TYPE(std::sin( 1.0    )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)( -EVE_TYPE(1)  ) , EVE_TYPE(std::sin(-1.0    )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)( pio2   ) , EVE_TYPE(std::sin( vpio2  )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)(-pio2   ) , EVE_TYPE(std::sin(-vpio2  )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)( pio4   ) , EVE_TYPE(std::sin( vpio4  )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)(-pio4   ) , EVE_TYPE(std::sin(-vpio4  )), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)( pio4/2 ) , EVE_TYPE(std::sin( vpio4/2)), 0.5);
  TTS_ULP_EQUAL(eve::small(eve::sin)(-pio4/2 ) , EVE_TYPE(std::sin(-vpio4/2)), 0.5);
}
