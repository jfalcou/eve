//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/memory/is_aligned.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE( "is_aligned for integers" )
{
  TTS_EXPECT( eve::is_aligned<1>(0) );
  TTS_EXPECT( eve::is_aligned<1>(1) );
  TTS_EXPECT( eve::is_aligned<1>(2) );

  TTS_EXPECT( eve::is_aligned<2>(0)   );
  TTS_EXPECT_NOT( eve::is_aligned<2>(1)  );
  TTS_EXPECT( eve::is_aligned<2>(2)   );
  TTS_EXPECT( eve::is_aligned<2>(4)   );

  TTS_EXPECT( eve::is_aligned<4>(0)   );
  TTS_EXPECT_NOT( eve::is_aligned<4>(1)  );
  TTS_EXPECT_NOT( eve::is_aligned<4>(2)  );
  TTS_EXPECT( eve::is_aligned<4>(4)   );
  TTS_EXPECT( eve::is_aligned<4>(8)   );

  TTS_EXPECT( eve::is_aligned<8>(0)   );
  TTS_EXPECT_NOT( eve::is_aligned<8>(1)  );
  TTS_EXPECT_NOT( eve::is_aligned<8>(2)  );
  TTS_EXPECT_NOT( eve::is_aligned<8>(4)   );
  TTS_EXPECT( eve::is_aligned<8>(8)   );
  TTS_EXPECT( eve::is_aligned<8>(16)   );
}
