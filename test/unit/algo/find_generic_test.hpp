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

#include <algorithm>
#include <vector>

namespace algo_test
{
  template <typename T, typename Algo, typename Check>
  void find_one_ptr_test(T* f, T* l, T* res, Algo alg, Check check)
  {
    auto pred = [](auto x) { return x != 0; };
    check(f, l, res, alg(f, l, pred));

    if (eve::is_aligned<eve::expected_cardinal_v<T> * sizeof(T)>(f))
    {
      auto f_ = eve::aligned_ptr<T>(f);
      check(f_, l, res, alg(f_, l, pred));
    }
  }

  template <typename T, typename Algo, typename Check>
  void find_generic_test_page_ends(eve::as_<T>, Algo alg, Check check)
  {
    using e_t = eve::element_type_t<T>;
    std::vector<e_t, eve::aligned_allocator<e_t, 4096>> page(4096 / sizeof(e_t), e_t{0});

    constexpr int elements_to_test  = std::min(T::size() * 10, 300l);

    auto f = page.data();
    auto l = f + elements_to_test;

    auto run = [&] {
      for (auto it = f; it < l; ++it) {
        find_one_ptr_test(f, l, l, alg, check);
        *it = 1;

        find_one_ptr_test(f, l, it, alg, check);
        *it = 0;
      }
    };

    // from the beginning
    while (f < l) {
      run();
      if (l != (page.data() + page.size())) { *l = 1; }
      --l;
      *f = 1;
      ++f;
    }

    std::fill(page.begin(), page.end(), 0);

    l = page.data() + page.size();
    f = l - elements_to_test;

    // from the end
    while (f < l) {
      run();
      if (l != (page.data() + page.size())) { *l = 1; }
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
