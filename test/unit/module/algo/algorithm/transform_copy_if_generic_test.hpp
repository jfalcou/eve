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
#include <random>
#include <vector>

namespace algo_test
{

template<typename Algo, typename Op, typename T> struct transform_copy_if_ptr_test
{
  Algo                                alg;
  Op                                  op;
  std::vector<eve::element_type_t<T>> buf1;
  std::vector<eve::element_type_t<T>> buf2;
  std::mt19937                        g {T::size()};

  transform_copy_if_ptr_test(Algo a, Op o) : alg(a), op(o) {}

  void init(auto *page_begin, auto *, auto *, auto *page_end)
  {
    std::iota(page_begin, page_end, 1);
    std::fill(page_begin, page_begin + 300, 0);
    std::shuffle(page_begin, page_end, g);
  }

  void run(auto rng)
  {
    buf1.clear();
    buf2.resize(rng.end() - rng.begin());

    auto p = [](auto x) { return x != 0; };

    auto func = [&](auto x) { return kumi::make_tuple(op(x), p(x)); };

    std::copy_if(eve::unalign(rng.begin()), eve::unalign(rng.end()), std::back_inserter(buf1), p);
    std::transform(eve::unalign(buf1.begin()), eve::unalign(buf1.end()), buf1.begin(), op);

    buf2.erase(alg(rng, buf2, func), buf2.end());
    TTS_EQUAL(buf1, buf2, REQUIRED);

    if( buf2.empty() ) return;

    buf2.pop_back();
    auto end1 = alg(rng, buf2, func);

    TTS_EQUAL(buf2.end() - end1, 0, REQUIRED);

    buf1.pop_back();
    TTS_EQUAL(buf1, buf2, REQUIRED);
  }

  void adjust(auto *, auto *f, auto *l, auto *page_end)
  {
    *f = 1;
    if( l != page_end ) *l = 1;
  }
};

template<typename T, typename Algo, typename Op>
void
transform_copy_if_test_page_ends(eve::as<T> tgt, Algo alg, Op op)
{
  algo_test::page_ends_test(tgt, transform_copy_if_ptr_test<Algo, Op, T> {alg, op});
}

template<typename T, typename Algo, typename Op>
void
transform_copy_if_generic_test(eve::as<T> as_t, Algo alg, Op op)
{
  transform_copy_if_test_page_ends(eve::as<eve::nofs_wide<typename T::value_type>> {}, alg, op);
  transform_copy_if_test_page_ends(as_t, alg[eve::algo::force_cardinal<T::size()>], op);
}

}
