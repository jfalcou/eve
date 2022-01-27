//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
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
