//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check bitofsign return type")
{
  using eve::bitofsign;
  TTS_EXPR_IS(bitofsign(Type()), (Type));
}

TTS_CASE("Check eve::bitofsign behavior")
{
  using eve::all;
  using eve::bitofsign;
  using eve::is_positive;
  using eve::is_negative;

  if constexpr( std::is_floating_point_v<Value>)
  {
    if constexpr( eve::platform::supports_infinites )
    {
      TTS_EQUAL( bitofsign(eve::Inf<Type>() ), Type(0)           );
      TTS_EQUAL( bitofsign(eve::Minf<Type>()), eve::Mzero<Type>());
      TTS_EXPECT( all(is_positive(bitofsign( eve::Inf<Type>()))) );
      TTS_EXPECT( all(is_negative(bitofsign(eve::Minf<Type>()))) );
    }

    TTS_EQUAL (bitofsign(Type(0))           , Type(0));
    TTS_EQUAL (bitofsign(eve::Mzero<Type>()), eve::Mzero<Type>());
    TTS_EXPECT( all(is_positive(bitofsign(Type(0)))) );
    TTS_EXPECT( all(is_negative(bitofsign(eve::Mzero<Type>()))) );

    TTS_EQUAL (bitofsign(Type(1)), Type(0));
    TTS_EXPECT( all(is_positive(bitofsign(Type(1)))) );

    TTS_EQUAL (bitofsign(Type(-1)), eve::Mzero<Type>());
    TTS_EXPECT( all(is_negative(bitofsign(Type(-1)))) );
  }
  else if constexpr( std::is_unsigned_v<Value>)
  {
    TTS_EQUAL(bitofsign(Type(1)), Type(0));
    TTS_EQUAL(bitofsign(eve::Valmax<Type>()), Type(1ull << (sizeof(Value)*8-1)));
  }
  else
  {
    TTS_EQUAL(bitofsign(Type(-1)), Type(1ull << (sizeof(Value)*8-1)));
    TTS_EQUAL(bitofsign(Type( 1)), Type(0));
    TTS_EQUAL(bitofsign(Type( 0)), Type(0));
  }
}
