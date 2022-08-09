//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

TTS_CASE("supports bmi well") {
  if constexpr (eve::current_api == eve::avx512)
  {
    TTS_CONSTEXPR_EXPECT(eve::supports_bmi_well);
  }
  else
#ifdef EVE_USE_BMI_ON_AVX2
  if constexpr (eve::current_api == eve::avx2)
  {
    TTS_CONSTEXPR_EXPECT(eve::supports_bmi_well);
  }
  else
#endif
  {
    TTS_CONSTEXPR_EXPECT_NOT(eve::supports_bmi_well);
  }
};
