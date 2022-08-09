//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/iota.hpp>

#include "transform_inplace_generic_test.hpp"

#include <numeric>

TTS_CASE_TPL("Check iota", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_inplace_generic_test(
    eve::as<T>{},
    eve::algo::iota,
    [](auto f, auto l, auto o, auto init) {
      std::iota(o, o + (l - f), init);
    },
    0
  );
};
