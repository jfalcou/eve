//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/reverse.hpp>

#include "transform_inplace_generic_test.hpp"

#include <algorithm>

TTS_CASE_TPL("Check reverse inplace", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_inplace_generic_test(
    eve::as<T>{},
    eve::algo::reverse,
    [](auto f, auto l, auto o) {
      std::reverse_copy(f, l, o);
    }
  );
};
