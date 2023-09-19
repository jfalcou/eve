//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle_v2/shuffle_v2_test.hpp"

namespace
{

TTS_CASE_TPL("Check reverse, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  shuffle_test::named_shuffle1_test<
      /*supports_G_eq_T_Size*/ true>(eve::as<T> {}, eve::reverse);
};

} // namespace
