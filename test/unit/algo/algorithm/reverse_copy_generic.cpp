//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/reverse.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

EVE_TEST_TYPES("Check reverse_copy", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_to_generic_test(
    tgt,
    eve::algo::reverse_copy,
    [](auto f, auto l, auto o) {
      std::reverse_copy(f, l, o);
    }
  );
};
