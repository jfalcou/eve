//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

TTS_CASE_TPL("Check copy to a different range", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_to_generic_test(
    eve::as<T>{},
    eve::algo::copy,
    [](auto f, auto l, auto o) {
      std::copy(f, l, o);
    }
  );
};
