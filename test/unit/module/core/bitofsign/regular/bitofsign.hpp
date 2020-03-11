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
  TTS_EXPR_IS(bitofsign(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::bitofsign behavior")
{
  using eve::all;
  using eve::bitofsign;
  using eve::is_positive;
  using eve::is_negative;

  if constexpr( std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr( eve::platform::supports_infinites )
    {
      TTS_EQUAL( bitofsign(eve::Inf<EVE_TYPE>() ), EVE_TYPE(0)           );
      TTS_EQUAL( bitofsign(eve::Minf<EVE_TYPE>()), eve::Mzero<EVE_TYPE>());
      TTS_EXPECT( all(is_positive(bitofsign( eve::Inf<EVE_TYPE>()))) );
      TTS_EXPECT( all(is_negative(bitofsign(eve::Minf<EVE_TYPE>()))) );
    }

    TTS_EQUAL (bitofsign(EVE_TYPE(0))           , EVE_TYPE(0));
    TTS_EQUAL (bitofsign(eve::Mzero<EVE_TYPE>()), eve::Mzero<EVE_TYPE>());
    TTS_EXPECT( all(is_positive(bitofsign(EVE_TYPE(0)))) );
    TTS_EXPECT( all(is_negative(bitofsign(eve::Mzero<EVE_TYPE>()))) );

    TTS_EQUAL (bitofsign(EVE_TYPE(1)), EVE_TYPE(0));
    TTS_EXPECT( all(is_positive(bitofsign(EVE_TYPE(1)))) );

    TTS_EQUAL (bitofsign(EVE_TYPE(-1)), eve::Mzero<EVE_TYPE>());
    TTS_EXPECT( all(is_negative(bitofsign(EVE_TYPE(-1)))) );
  }
  else if constexpr( std::is_unsigned_v<EVE_VALUE>)
  {
    TTS_EQUAL(bitofsign(EVE_TYPE(1)), EVE_TYPE(0));
    TTS_EQUAL(bitofsign(eve::Valmax<EVE_TYPE>()), EVE_TYPE(1ull << (sizeof(EVE_VALUE)*8-1)));
  }
  else
  {
    TTS_EQUAL(bitofsign(EVE_TYPE(-1)), EVE_TYPE(1ull << (sizeof(EVE_VALUE)*8-1)));
    TTS_EQUAL(bitofsign(EVE_TYPE( 1)), EVE_TYPE(0));
    TTS_EQUAL(bitofsign(EVE_TYPE( 0)), EVE_TYPE(0));
  }
}
