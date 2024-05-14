//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE("eve.module.core, irregular_predicate") {
  TTS_CONSTEXPR_EXPECT(eve::irregular_predicate<bool(*)()>);
  TTS_CONSTEXPR_EXPECT((eve::irregular_predicate<bool(*)(int), int>));
  TTS_CONSTEXPR_EXPECT((eve::irregular_predicate<int(*)(int), int>));

  TTS_CONSTEXPR_EXPECT(!(eve::irregular_predicate<int(*)(int), std::string>));
  TTS_CONSTEXPR_EXPECT(!(eve::irregular_predicate<int>));
};
