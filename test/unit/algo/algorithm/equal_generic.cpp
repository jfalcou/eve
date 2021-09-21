//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/equal.hpp>

#include "mismatch_generic_test.hpp"

EVE_TEST_TYPES("eve.algo.equal generic", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::mismatch_generic_test(tgt, eve::algo::equal,
    [](auto, auto zip_l, auto expected, bool actual) {
     TTS_EQUAL((expected == zip_l), actual);
  });
};
