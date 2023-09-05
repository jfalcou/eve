//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/module/algo.hpp>

namespace algo_test
{
  template <typename>
  struct read_to_load_match
  {
    static constexpr std::ptrdiff_t value = 0;
  };


  template <typename I, typename S, typename T, typename ReplaceIgnored>
  void iterator_sentinel_test_one_pair(I f, S l, T v, ReplaceIgnored replace)
  {
    TTS_EQUAL     (eve::unalign(f), f);
    TTS_EQUAL     (eve::unalign(l), l);

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

    eve::fixed cardinal = eve::iterator_cardinal_t<I>{};
    TTS_TYPE_IS(eve::iterator_cardinal_t<I>, decltype(cardinal));
    TTS_TYPE_IS(decltype(l - f), std::ptrdiff_t);

    // read test
    {
      TTS_EQUAL(eve::read(f), eve::load(f).get(read_to_load_match<I>::value));
    }

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

  template <typename I>
  void previous_next_aligned(I f_)
  {
    auto f = eve::unalign(f_);
    if (f == f.previous_partially_aligned()) f += 1;

    if (eve::iterator_cardinal_v<I> != 1 && !eve::algo::always_aligned_iterator<I>) {
      TTS_EQUAL((f.next_partially_aligned() - f.previous_partially_aligned()), eve::iterator_cardinal_v<I>);
    }

    f = f.previous_partially_aligned();
    TTS_EQUAL(f.previous_partially_aligned(), f.next_partially_aligned());
  }

  template <typename I>
  void cardinal_cast_test(I f)
  {
    auto res = f.cardinal_cast(eve::lane<1>);
    TTS_TYPE_IS(typename decltype(res)::cardinal, eve::fixed<1>);
  }

  void is_relaxed_test(eve::algo::relaxed_iterator auto, eve::algo::relaxed_iterator auto) {}

  template <eve::algo::readable_iterator I, eve::algo::sentinel_for<I> S, typename T, typename ReplaceIgnored>
  void iterator_sentinel_test(I f, S l, T v, ReplaceIgnored replace)
  {
    TTS_CONSTEXPR_EXPECT(eve::algo::readable_iterator<I&>);

    eve::algo::preprocess_range(eve::algo::traits{}, f, f);
    is_relaxed_test(f, l);
    iterator_sentinel_test_one_pair(f, l, v, replace);
    unaligned_iteration_test(eve::unalign(f), l);

    TTS_CONSTEXPR_EXPECT(
      eve::algo::partially_aligned_iterator<decltype(f.previous_partially_aligned())>);
    TTS_CONSTEXPR_EXPECT(
      eve::algo::partially_aligned_iterator<decltype(f.next_partially_aligned())>);
    TTS_CONSTEXPR_EXPECT(
      eve::algo::unaligned_iterator<decltype(eve::unalign(f))>);

    previous_next_aligned(f);

    iterator_sentinel_test_one_pair(eve::unalign(f), l, v, replace);
    iterator_sentinel_test_one_pair(f, eve::unalign(l), v, replace);
    iterator_sentinel_test_one_pair(eve::unalign(f), eve::unalign(l), v, replace);
  }

  template <typename I, typename T, typename ReplaceIgnored>
  void writeable_readable_iterator(I f, T v, ReplaceIgnored replace)
  {
    auto or_ = replace(v, eve::ignore_all);
    eve::store(or_, f);
    TTS_EQUAL(eve::load(f), or_);

    eve::store(v, f);

    // write
    {
      eve::write(or_.get(0),f);
      TTS_EQUAL(eve::read(f), or_.get(0));
      eve::store(v, f);
    }

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

    if constexpr (!std::same_as<eve::unaligned_t<I>, I>)
    {
      writeable_readable_iterator(eve::unalign(f), v, replace);
    }
  }

  template <typename I, typename T, typename ReplaceIgnored>
  void iterator_supports_compress(I f, T v, ReplaceIgnored replace)
  {
    auto or_ = replace(v, eve::ignore_all);
    eve::store(or_, f);

    T expected = or_;
    expected.set(0, v.back());

    eve::logical<eve::wide<std::uint16_t, eve::fixed<T::size()>>> mask{false};
    mask.set(T::size() - 1, true);
    eve::unaligned_t<I> res = eve::compress_store[eve::safe](v, mask, f);
    TTS_EQUAL(eve::load(f), expected);
    TTS_EQUAL((res - f), 1);

    eve::store(v, f);
  }
}
