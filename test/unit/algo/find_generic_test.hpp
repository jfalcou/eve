//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/memory/aligned_allocator.hpp>

#include <vector>

namespace algo_test
{
  template <typename T, typename Test>
  void find_generic_test_page_ends(eve::as_<T>, Test test)
  {
    using e_t = eve::element_type_t<T>;
    std::vector<e_t, eve::aligned_allocator<e_t, 4096>> page(4096 / sizeof(e_t), e_t{0});

    const std::ptrdiff_t elemenents_to_test = 512 / T::static_size;

    auto f = page.begin();
    auto l = page.begin() + elemenents_to_test;

    auto run = [&] {
      for (auto it = f; it < l; ++it) {
        test(f, l, l);
        *it = 1;
        test(f, l, it);
        *it = 0;
      }
    };

    // from the beginning
    while (f < l) {
      run();
      *l = 1;
      --l;
      *f = 1;
      ++f;
    }

    std::fill(page.begin(), page.end(), 0);

    // from the end
    while (f < l) {
      run();
      *l = 1;
      --l;
      *f = 1;
      ++f;
    }
  }

  template <typename T, typename Test>
  void find_generic_test(eve::as_<T> as_t, Test test)
  {
    find_generic_test_page_ends(as_t, test);
  }
}
