//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

TTS_CASE_TPL("Check trasnform_to", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_to_generic_test(
    eve::as<T>{},
    eve::algo::transform_to,
    [](auto f, auto l, auto o, auto op) {
      (void)op;
      std::transform(f, l, o,
      [](auto x) { return static_cast<decltype(x)>(x + x); });
    },
    [](auto x) { return x + x; }
  );
};
