//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "transform_inplace_generic_test.hpp"

#include <numeric>

TTS_CASE_TPL("Check fill", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_inplace_generic_test(
    eve::as<T>{},
    eve::algo::fill,
    [](auto f, auto l, auto o, auto v) {
      std::fill(o, o + (l - f), v);
    },
    5
  );
};
