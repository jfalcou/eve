//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/traits/underlying_type.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for underlying_type: scalar types")
{
  using eve::logical;

  TTS_TYPE_IS( eve::underlying_type_t<bool>                             , bool          );
  TTS_TYPE_IS( eve::underlying_type_t<int>                              , int           );
  TTS_TYPE_IS( eve::underlying_type_t<logical<int>>                     , logical<int>  );
};

TTS_CASE( "Check for underlying_type: SIMD types")
{
  using eve::logical;
  using eve::wide;

  TTS_TYPE_IS((eve::underlying_type_t<wide<int,eve::fixed<8>>>)               , int           );
  TTS_TYPE_IS( eve::underlying_type_t<wide<int>>                              , int           );
  TTS_TYPE_IS( eve::underlying_type_t<logical<wide<int>>>                     , logical<int>  );
};
