//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/transform.hpp>

#include "transform_inplace_generic_test.hpp"

#include <algorithm>

TTS_CASE_TPL("Check transform_inplace", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_inplace_generic_test(
    eve::as<T>{},
    eve::algo::transform_inplace,
    [](auto f, auto l, auto o, auto op) {
      std::transform(f, l, o, op);
    },
    [](auto x) { return x + x; }
  );
};
