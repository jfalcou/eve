//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
