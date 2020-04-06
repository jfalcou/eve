//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <tts/tests/types.hpp>
#include <eve/concept/rebindable.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tuple>
#include <array>

TTS_CASE("Checck that non-rebindable types don't satisfy rebindbale" )
{
  TTS_EXPECT_NOT( eve::rebindable<int>   );
  TTS_EXPECT_NOT( eve::rebindable<char>  );
  TTS_EXPECT_NOT( eve::rebindable<float> );
  TTS_EXPECT_NOT( eve::rebindable<double>);

  TTS_EXPECT_NOT( eve::rebindable<eve::logical<short>>);
  TTS_EXPECT_NOT( eve::rebindable<eve::logical<float>>);
}

TTS_CASE("Checck that wide satisfies rebindbale" )
{
  TTS_EXPECT( eve::rebindable<eve::wide<int>>   );
  TTS_EXPECT( eve::rebindable<eve::logical<eve::wide<float>>>);
}

TTS_CASE("Checck that tuple-like types satisfy rebindbale" )
{
  TTS_EXPECT( (eve::rebindable<std::pair<int,float>>)             );
  TTS_EXPECT( (eve::rebindable<std::array<double,7>>)             );
  TTS_EXPECT( (eve::rebindable<std::tuple<char,short,int,long>>)  );
}
