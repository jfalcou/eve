//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/algo/traits.hpp>

#include <eve/memory/aligned_allocator.hpp>

#include <vector>

namespace algo_test
{
  template <typename T, typename Algo, typename Check>
  void find_generic_test_page_ends(eve::as_<T>, Algo alg, Check check)
  {
    using e_t = eve::element_type_t<T>;
    std::vector<e_t, eve::aligned_allocator<e_t, 4096>> page(4096 / sizeof(e_t), e_t{0});

    const std::ptrdiff_t elemenents_to_test = 512 / T::static_size;

    auto f = page.begin();
    auto l = page.begin() + elemenents_to_test;

    auto run = [&] {
      for (auto it = f; it < l; ++it) {
        auto actual = alg(f, l, [](auto x) { return x != 0; });
        check(f, l, l, actual);
        *it = 1;

        actual = alg(f, l, [](auto x) { return x != 0; });
        check(f, l, it, actual);
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

  template <typename T, typename Algo, typename Check>
  void find_generic_test(eve::as_<T> as_t, Algo alg, Check check)
  {
    find_generic_test_page_ends(as_t, alg, check);

    find_generic_test_page_ends(as_t, [alg](auto ... args) {
      return alg(eve::algo::traits(eve::algo::unroll<1>), args...);
    }, check);

    find_generic_test_page_ends(as_t, [alg](auto ... args) {
      return alg(eve::algo::traits(eve::algo::unroll<2>), args...);
    }, check);

    find_generic_test_page_ends(as_t, [alg](auto ... args) {
      return alg(eve::algo::traits(eve::algo::unroll<3>), args...);
    }, check);

    find_generic_test_page_ends(as_t, [alg](auto ... args) {
      return alg(eve::algo::traits(eve::algo::unroll<4>), args...);
    }, check);
  }
}
