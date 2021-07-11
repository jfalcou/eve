//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/algo/as_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/memory/aligned_allocator.hpp>

#include <algorithm>
#include <vector>

namespace algo_test
{
  template <typename T, typename U, typename Algo, typename Check>
  void find_one_ptr_test(eve::as<T>, U* f, U* l, U* res, Algo alg, Check check)
  {
    auto pred = [](auto x) { return x != 0; };
    check(f, l, res, alg(eve::algo::as_range(f, l), pred));

    static constexpr std::ptrdiff_t alignment = T::size() * sizeof(U);
    using a_p = eve::aligned_ptr<U, eve::fixed<T::size()>>;

    if (eve::is_aligned<alignment>(f))
    {
      auto f_ = a_p(f);
      check(f_, l, res, alg(eve::algo::as_range(f_, l), pred));

      if (eve::is_aligned<alignment>(l))
      {
        auto l_ = a_p(l);
        check(f_, l_, res, alg(eve::algo::as_range(f_, l_), pred));
      }
    }
  }

  template <typename T, typename Algo, typename Check>
  void find_generic_test_page_ends(eve::as<T> tgt, Algo alg, Check check)
  {
    using e_t     = eve::element_type_t<T>;
    using card_t  = eve::fixed<4096/ sizeof(e_t)>;
    std::vector<e_t, eve::aligned_allocator<e_t, card_t>> page(card_t::value, e_t{0});

    constexpr int elements_to_test  = std::min(T::size() * 10, 300l);

    auto f = page.data();
    auto l = f + elements_to_test;

    auto run = [&] {
      for (auto it = f; it < l; ++it) {
        find_one_ptr_test(tgt, f, l, l, alg, check);
        *it = 1;

        find_one_ptr_test(tgt, f, l, it, alg, check);
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
  void find_generic_test(eve::as<T> as_t, Algo alg, Check check)
  {
    find_generic_test_page_ends(eve::as<eve::wide<typename T::value_type>>{}, alg, check);

    find_generic_test_page_ends(as_t, alg[
      eve::algo::traits{eve::algo::force_cardinal<T::size()>, eve::algo::unroll<1>}], check);
    find_generic_test_page_ends(as_t, alg[
      eve::algo::traits{eve::algo::force_cardinal<T::size()>, eve::algo::unroll<2>}], check);
    find_generic_test_page_ends(as_t, alg[
      eve::algo::traits{eve::algo::force_cardinal<T::size()>, eve::algo::unroll<3>}], check);
    find_generic_test_page_ends(as_t, alg[eve::algo::traits{
      eve::algo::force_cardinal<T::size()>, eve::algo::unroll<4>}], check);
  }
}
