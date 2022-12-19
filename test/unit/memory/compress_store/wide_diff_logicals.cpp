//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_store_test.hpp"
#include <eve/module/core.hpp>


TTS_CASE_WITH( "Check compress store behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1))
        )
<typename T> ([[maybe_unused]] T data)
{
#if !defined(SPY_SIMD_IS_ARM_FIXED_SVE)
  using N = eve::fixed<T::size()>;
  smaller_test_v<eve::logical<eve::wide<std::uint8_t,  N>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint16_t, N>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint32_t, N>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint64_t, N>>>(data);
#else
  TTS_PASS("Not tested for SVE at the moment");
#endif
};
