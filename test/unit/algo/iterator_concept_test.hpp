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
  template <typename I, typename S, typename Delegate>
  void iterator_sentinel_test_one_pair(I f, S l, Delegate delegate)
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
      delegate.assert_eq(eve::load(f), delegate.v());

      auto ignore_test = [&](auto ignore) {
        auto expected = delegate.replace(delegate.v(), ignore);
        delegate.assert_eq(eve::load[ignore.else_(0)](f), expected);
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

  template <typename I, typename S, typename Delegate>
  void iterator_sentinel_test(I f, S l, Delegate delegate)
  {
    iterator_sentinel_test_one_pair(f, l, delegate);
    unaligned_iteration_test(f.unaligned(), l);

    iterator_sentinel_test_one_pair(f.unaligned(), l, delegate);
    iterator_sentinel_test_one_pair(f, l.unaligned(), delegate);
    iterator_sentinel_test_one_pair(f.unaligned(), l.unaligned(), delegate);
  }

  template <typename I, typename Delegate>
  void writeable_readable_iterator(I f, Delegate delegate)
  {
    auto or_ = delegate.replace(delegate.v(), eve::ignore_all);
    eve::store(or_, f);
    delegate.assert_eq(eve::load(f), or_);
    eve::store(delegate.v(), f);

    auto ignore_test = [&](auto ignore)
    {
      auto expected = delegate.replace(delegate.v(), ignore);

      eve::store[ignore.else_(0)](delegate.v(), f);
      delegate.assert_eq(eve::load(f), expected);

      eve::store(delegate.v(), f);
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
      writeable_readable_iterator(f.unaligned(), delegate);
    }
  }
}
