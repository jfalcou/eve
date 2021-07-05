//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/reduce.hpp>

EVE_TEST_TYPES("Check reduce", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  std::vector<char> v{1, 2, 3};
  TTS_EQUAL(eve::algo::reduce(v, 0.0), 6.0);
};
