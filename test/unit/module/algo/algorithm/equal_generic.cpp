//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "mismatch_generic_test.hpp"

TTS_CASE_TPL("eve.algo.equal generic", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  algo_test::mismatch_generic_test(eve::as<T>{}, eve::algo::equal,
    [](auto, auto zip_l, auto expected, bool actual) {
     TTS_EQUAL((expected == zip_l), actual);
  });
};
