//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <algorithm>
#include <vector>

namespace algo_test
{
template<typename Algo, typename Check> struct find_last_ptr_test
{
  Algo  alg;
  Check check;

  find_last_ptr_test(Algo alg, Check check) : alg(alg), check(check) {}

  void init(auto *page_begin, auto *, auto *, auto *page_end) const
  {
    std::fill(page_begin, page_end, 1);
  }

  void run(auto rng) const
  {
    auto *f = eve::unalign(rng.begin());
    auto *l = eve::unalign(rng.end());

    auto pred = [](auto x) { return x != 0; };

    if( f == l )
    {
      check(f, l, l, alg(rng, pred));
      return;
    }

    for( auto *it = l - 1; it != f; --it )
    {
      check(f, l, it, alg(rng, pred));
      *it = 0;
    }

    std::fill(f, l, 1);
  }

  void adjust(auto *, auto *f, auto *l, auto *page_end) const
  {
    *f = 1;
    if( l != page_end ) *l = 1;
  }
};

template<typename T, typename Algo, typename Check>
void
find_generic_backward_test_page_ends(eve::as<T> tgt, Algo alg, Check check)
{
  algo_test::page_ends_test(tgt, find_last_ptr_test {alg, check});
}

template<typename T, typename Algo, typename Check>
void
find_generic_backward_test(eve::as<T> as_t, Algo alg, Check check)
{
  find_generic_backward_test_page_ends(eve::as<eve::nofs_wide<typename T::value_type>> {}, alg, check);

  find_generic_backward_test_page_ends(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<1>], check);
  find_generic_backward_test_page_ends(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<2>], check);
  find_generic_backward_test_page_ends(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<3>], check);
  find_generic_backward_test_page_ends(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<4>], check);
}
}
