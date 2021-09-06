//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/mismatch.hpp>

#include "mismatch_generic_test.hpp"

EVE_TEST_TYPES("eve.algo.mismatch generic", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::mismatch_generic_test(tgt, eve::algo::mismatch,
    [](auto zip_f, auto /*zip_l*/, auto expected, auto actual) {
     TTS_EQUAL((expected - zip_f), (actual - zip_f));
  });
};
