//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/copy.hpp>

#include <eve/algo/as_range.hpp>

#include <algorithm>

EVE_TEST_TYPES("Check that we can copy to an address after beginning (copy/copy_backward difference)",
               algo_test::selected_types)
<typename T>(eve::as<T>)
{
  auto page = algo_test::allocate_page<eve::element_type_t<T>>();
  std::iota(page.begin(), page.end(), 0);

  const std::ptrdiff_t r_size = 300;

  for (int i = 0; i != T::size(); ++i) {
    for (int j = i; j != T::size() * 2; ++j) {
      auto from = page.begin() + i;
      auto to = page.begin() + j;
      auto r = eve::algo::as_range(from, from + r_size);

      std::vector<eve::element_type_t<T>> expected(from, from + r_size);

      eve::algo::copy_backward[eve::algo::force_cardinal<T::size()>](r, to);

      std::vector<eve::element_type_t<T>> actual(to, to + r_size);

      TTS_EQUAL(expected, actual);
    }
  }
};
