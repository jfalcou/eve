//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/arch.hpp>

TTS_CASE("Check that aggregated_ ABI differs with architecture specificities" )
{
# if defined(SPY_SIMD_IS_X86_AVX512) || defined(SPY_SIMD_IS_ARM_FIXED_SVE)
  TTS_EXPECT_NOT( eve::aggregated_::is_wide_logical );
# else
  TTS_EXPECT( eve::aggregated_::is_wide_logical );
# endif
};

int aggregation_kind( eve::internal_wide_logical::aggregated_ ) { return +1; }
int aggregation_kind( eve::internal_bit_logical::aggregated_  ) { return -1; }

TTS_CASE("Check that aggregated_ ABI participates to function mangling" )
{
# if defined(SPY_SIMD_IS_X86_AVX512) || defined(SPY_SIMD_IS_ARM_FIXED_SVE)
  TTS_EQUAL( aggregation_kind(eve::aggregated_{}), -1);
# else
  TTS_EQUAL( aggregation_kind(eve::aggregated_{}), +1);
# endif
};
