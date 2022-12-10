//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE("Check validation of the scalar_value concept" )
{
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_EXPECT( eve::scalar_value<int>   );
  TTS_EXPECT( eve::scalar_value<float> );
  TTS_EXPECT( eve::scalar_value<double>);

  TTS_EXPECT( eve::scalar_value<logical<short>>);
  TTS_EXPECT( eve::scalar_value<logical<float>>);

  TTS_EXPECT( (eve::scalar_value<kumi::tuple<int,float>>) );

  TTS_EXPECT_NOT( (eve::scalar_value<char>                        ) );
  TTS_EXPECT_NOT( (eve::scalar_value<wide<int>>                   ) );
  TTS_EXPECT_NOT( (eve::scalar_value<logical<wide<int>>>          ) );
  TTS_EXPECT_NOT( (eve::scalar_value<wide<std::int8_t,fixed<16>>> ) );
  TTS_EXPECT_NOT( (eve::scalar_value<wide<kumi::tuple<int,float>>>) );
};

TTS_CASE("Check validation of the simd_value" )
{
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_EXPECT_NOT( eve::simd_value<int>   );
  TTS_EXPECT_NOT( eve::simd_value<char>  );
  TTS_EXPECT_NOT( eve::simd_value<float> );
  TTS_EXPECT_NOT( eve::simd_value<double>);

  TTS_EXPECT_NOT( eve::simd_value<logical<short>>);
  TTS_EXPECT_NOT( eve::simd_value<logical<float>>);

  TTS_EXPECT_NOT( (eve::simd_value<kumi::tuple<int,float>>) );

  TTS_EXPECT( (eve::simd_value<wide<int>>           ) );
  TTS_EXPECT( (eve::simd_value<logical<wide<int>>>  ) );
  TTS_EXPECT( (eve::simd_value<wide<std::int8_t,fixed<16>>>) );
  TTS_EXPECT( (eve::simd_value<wide<kumi::tuple<int,float>>>) );
};
