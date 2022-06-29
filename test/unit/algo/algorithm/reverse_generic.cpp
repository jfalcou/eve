//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
