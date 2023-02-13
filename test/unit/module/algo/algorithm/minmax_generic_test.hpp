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
#include <algorithm>
#include <vector>

namespace algo_test
{
template<bool biggest, bool right, typename Algo, typename Check> struct minmax_ptr_test
{
  Algo        alg;
  Check       check;
  std::int8_t looking_for = 0;
  std::int8_t filler      = 5;

  minmax_ptr_test(Algo alg, Check check) : alg(alg), check(check)
  {
    if( biggest ) std::swap(looking_for, filler);
  }

  void init(auto *page_begin, auto *f, auto *l, auto *page_end) const
  {
    std::fill(page_begin, page_end, looking_for);
    std::fill(f, l, filler);
  }

  void run(auto rng) const requires(!right)
  {
    auto *f = eve::unalign(rng.begin());
    auto *l = eve::unalign(rng.end());

    check(f, l, f, alg(rng));

    if (f != l) {
      *(l - 1) = looking_for;
    }

    for( auto *it = f; it != l; ++it )
    {
      *it = looking_for;
      check(f, l, it, alg(rng));
      *it = filler;
    }
  }

  void run(auto rng) const requires(right)
  {
    auto *f = eve::unalign(rng.begin());
    auto *l = eve::unalign(rng.end());

    if( f == l ) { check(f, l, f, alg(rng)); }
    else { check(f, l, l - 1, alg(rng)); }

    if (f != l) {
      *f = looking_for;
    }

    for( auto *it = l; it != f; )
    {
      --it;
      *it = looking_for;
      check(f, l, it, alg(rng));
      *it = filler;
    }
  }

  void adjust(auto *, auto *f, auto *l, auto *page_end) const
  {
    *f = looking_for;
    if( l != page_end ) *l = looking_for;
  }
};

template<bool biggest, bool right, typename T, typename Algo, typename Check>
void
minmax_generic_test_page_ends(eve::as<T> tgt, Algo alg, Check check)
{
  algo_test::page_ends_test(tgt, minmax_ptr_test<biggest, right, Algo, Check> {alg, check});
}

template<bool biggest, bool right, typename T, typename Algo, typename Check>
void
minmax_generic_test(eve::as<T> as_t, Algo alg, Check check)
{
  minmax_generic_test_page_ends<biggest, right>(
      eve::as<eve::nofs_wide<typename T::value_type>> {}, alg, check);

  minmax_generic_test_page_ends<biggest, right>(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<1>], check);
  minmax_generic_test_page_ends<biggest, right>(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<2>], check);
  minmax_generic_test_page_ends<biggest, right>(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<3>], check);
  minmax_generic_test_page_ends<biggest, right>(
      as_t, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<4>], check);
}
}
