//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <algorithm>

TTS_CASE_TPL("Check that we can copy to an address before beginning (copy/copy_backward difference)",
               algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto page = algo_test::allocate_page<eve::element_type_t<T>>();
  std::iota(page.begin(), page.end(), 0);

  const std::ptrdiff_t r_size = 300;

  for (int i = 0; i != T::size(); ++i) {
    for (int j = i; j != T::size() * 2; ++j) {
      auto from = page.begin() + j;
      auto r = eve::algo::as_range(from, from + r_size);

      std::vector<eve::element_type_t<T>> expected(from, from + r_size);

      eve::algo::copy[eve::algo::force_cardinal<T::size()>](r, page.begin() + i);

      std::vector<eve::element_type_t<T>> actual(page.begin() + i, page.begin() + i + r_size);

      TTS_EQUAL(expected, actual);
    }
  }
};
