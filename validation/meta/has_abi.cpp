//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "driver.hpp"
#include <eve/detail/has_abi.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for detection of native ABI")
{
  TTS_EXPECT_NOT(( eve::has_native_abi_v<eve::wide<double, eve::fixed<32>>>              ));
  TTS_EXPECT_NOT(( eve::has_native_abi_v<eve::logical<eve::wide<double, eve::fixed<32>>>>));

#if defined(EVE_NO_SIMD)
  TTS_EXPECT_NOT( eve::has_native_abi_v<eve::wide<double>>                );
  TTS_EXPECT_NOT( eve::has_native_abi_v<eve::logical<eve::wide<double>>>  );
#else
  TTS_EXPECT( eve::has_native_abi_v<eve::wide<double>>                );
  TTS_EXPECT( eve::has_native_abi_v<eve::logical<eve::wide<double>>>  );
#endif

  TTS_EXPECT( eve::has_native_abi_v<double>                           );
  TTS_EXPECT( eve::has_native_abi_v<eve::logical<double>>             );
}

TTS_CASE( "Check for detection of aggregated ABI")
{
#if defined(EVE_NO_SIMD)
  TTS_EXPECT_NOT(( eve::has_aggregated_abi_v<eve::wide<double, eve::fixed<32>>>              ));
  TTS_EXPECT_NOT(( eve::has_aggregated_abi_v<eve::logical<eve::wide<double, eve::fixed<32>>>>));
#else
  TTS_EXPECT(( eve::has_aggregated_abi_v<eve::wide<double, eve::fixed<32>>>              ));
  TTS_EXPECT(( eve::has_aggregated_abi_v<eve::logical<eve::wide<double, eve::fixed<32>>>>));
#endif

  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::wide<double>>                );
  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::logical<eve::wide<double>>>  );

  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<double>                           );
  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::logical<double>>             );
}
