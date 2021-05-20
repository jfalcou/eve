//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/algo/concepts.hpp>

namespace algo_test
{
  template <typename I, typename S, typename T, typename ReplaceIgnored>
  void iterator_sentinel_test_one_pair(I f, S l, T v, ReplaceIgnored replace)
  {
    TTS_EQUAL     (f.unaligned(), f);
    TTS_EQUAL     (l.unaligned(), l);

    TTS_EQUAL     (f, f);
    TTS_LESS_EQUAL   (f, f);
    TTS_GREATER_EQUAL(f, f);
    TTS_EQUAL     (l, l);
    TTS_NOT_EQUAL (f, l);
    TTS_EXPECT_NOT(f == l);

    TTS_LESS         (f, l);
    TTS_LESS_EQUAL   (f, l);
    TTS_GREATER      (l, f);
    TTS_GREATER_EQUAL(l, f);

    eve::fixed cardinal = typename I::cardinal{};
    TTS_TYPE_IS(typename I::cardinal, decltype(cardinal));
    TTS_TYPE_IS(decltype(l - f), std::ptrdiff_t);

    {
      I next = f;
      next += cardinal();

      TTS_LESS         (f, next);
      TTS_LESS_EQUAL   (f, next);
      TTS_GREATER      (next, f);
      TTS_GREATER_EQUAL(next, f);

      TTS_EQUAL(next, (f + cardinal()));
      TTS_EQUAL((next - f), cardinal());

      next -= cardinal();
      TTS_EQUAL(f, next);
    }

    {
      TTS_EQUAL(eve::load(f), v);
      auto or_ = replace(v, eve::ignore_all);

      auto ignore_test = [&](auto ignore) {
        auto expected = replace(v, ignore);
        TTS_EQUAL(eve::load[ignore.else_(or_)](f), expected);
      };

      ignore_test(eve::ignore_none);
      ignore_test(eve::ignore_all);

      ignore_test(eve::keep_first(1));
      ignore_test(eve::ignore_first(1));

      ignore_test(eve::keep_last(1));
      ignore_test(eve::ignore_last(1));
      ignore_test(eve::keep_between(0, 1));
      ignore_test(eve::ignore_extrema(1, 0));
    }
  }

  template <typename I, typename S>
  void unaligned_iteration_test(I f, S l)
  {
    std::ptrdiff_t n = l - f;
    while (n) { f += 1; --n; }
    TTS_EQUAL(f, l);
  }

  template <eve::algo::readable_iterator I, eve::algo::sentinel_for<I> S, typename T, typename ReplaceIgnored>
  void iterator_sentinel_test(I f, S l, T v, ReplaceIgnored replace)
  {
    iterator_sentinel_test_one_pair(f, l, v, replace);
    unaligned_iteration_test(f.unaligned(), l);

    TTS_CONSTEXPR_EXPECT(
      eve::algo::partially_aligned_iterator<decltype(f.previous_partially_aligned())>);
    TTS_CONSTEXPR_EXPECT(
      eve::algo::unaligned_iterator<decltype(f.unaligned())>);

    iterator_sentinel_test_one_pair(f.unaligned(), l, v, replace);
    iterator_sentinel_test_one_pair(f, l.unaligned(), v, replace);
    iterator_sentinel_test_one_pair(f.unaligned(), l.unaligned(), v, replace);
  }

  template <typename I, typename T, typename ReplaceIgnored>
  void writeable_readable_iterator(I f, T v, ReplaceIgnored replace)
  {
    auto or_ = replace(v, eve::ignore_all);
    eve::store(or_, f);
    TTS_EQUAL(eve::load(f), or_);

    eve::store(v, f);

    auto ignore_test = [&](auto ignore)
    {
      auto expected = replace(v, ignore);

      eve::store[ignore.else_(or_)](v, f);
      TTS_EQUAL(eve::load(f), expected);

      eve::store(v, f);
    };

    ignore_test(eve::ignore_none);
    ignore_test(eve::ignore_all);

    ignore_test(eve::keep_first(1));
    ignore_test(eve::ignore_first(1));

    ignore_test(eve::keep_last(1));
    ignore_test(eve::ignore_last(1));
    ignore_test(eve::keep_between(0, 1));
    ignore_test(eve::ignore_extrema(1, 0));

    if constexpr (!std::same_as<eve::algo::unaligned_t<I>, I>)
    {
      writeable_readable_iterator(f.unaligned(), v, replace);
    }
  }
}
