//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/copy.hpp>

#include <eve/algo/as_range.hpp>

#include <algorithm>

TTS_CASE_TPL("Check that we can copy to an address after beginning (copy/copy_backward difference)",
               algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto page = algo_test::allocate_page<eve::element_type_t<T>>();
  std::iota(page.begin(), page.end(), 0);

  const std::ptrdiff_t r_size = 300;

  for (int i = 0; i != T::size(); ++i) {
    for (int j = i; j != T::size() * 2; ++j) {
      auto from = page.begin() + i;
      auto to = page.begin() + j;
      auto from_r = eve::algo::as_range(from, from + r_size);
      auto to_r = eve::algo::as_range(to, to + r_size);

      std::vector<eve::element_type_t<T>> expected(from, from + r_size);

      eve::algo::copy_backward[eve::algo::force_cardinal<T::size()>](from_r, to_r);

      std::vector<eve::element_type_t<T>> actual(to, to + r_size);

      TTS_EQUAL(expected, actual);
    }
  }
};
