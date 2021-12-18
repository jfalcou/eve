//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/copy.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

EVE_TEST_TYPES("Check copy to a different range", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_to_generic_test(
    tgt,
    eve::algo::copy_backward,
    [](auto f, auto l, auto o) {
      std::copy(f, l, o);
    }
  );
};
