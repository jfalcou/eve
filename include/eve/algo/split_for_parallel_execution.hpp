//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>


namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo
  //! @{
  //! @var split_for_parallel_execution
  //!
  //! @brief Callable object. A helper to write parallel algorithms on top of eve.
  //!        In eve we don't deal with threads but we can help you split into subtasks.
  //!
  //!        The purpose is to take a range and split it into subranges,
  //!        while trying to provide aligned subranges (so that only the sides operate on unaligned data).
  //!
  //!        For the same range/traits is guaranteed to do the same split.
  //!
  //!        By default we assume a cache line alignment, you can override with `eve::algo::force_cardinal` trait.
  //!
  //! **Required header:** `#include <eve/algo/split_for_parallel_execution.hpp>`
  //!
  //! | Member       | Effect                                                  |
  //! |:-------------|:-------------------------------------------------------:|
  //! | `operator()` | calls the delegate for each sub-range                   |
  //! | `operator[]` | constructs a version of the object with provided traits |
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template <relaxed_range R, typename Delegate>
  //!  std::ptrdiff_t operator()(R&& r, Delegate&& d, std::ptrdiff_t subtask_count, std::ptrdiff_t min_subtask_size);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! r                - relaxed range to be split
  //! Delegate d       - has methods: first_step, step, last_step accepting relaxed_range.
  //!                    first_step and last_step are guaranteed to be called, possibly with an empty range.
  //!                    (We do not define a proper concept, it is difficult).
  //! subtask_count    - how many subtasks (at the most) you want to spawn
  //! min_subtask_size - what's the minimal size of the subrange you need.
  //!
  //! **Return value**
  //!
  //! Number of non-empty subtasks
  //!
  //! FIX: #1000: we are underutilize alignment of boundaries.
  //!

  template <typename>
  struct print_type;

  template <typename TraitsSupport>
  struct split_for_parallel_execution_ : TraitsSupport
  {
    template <relaxed_range R, typename Delegate>
    std::ptrdiff_t operator()(R&& r,
                              Delegate&& d,
                              std::ptrdiff_t subtask_count,
                              std::ptrdiff_t min_subtask_size) const
    {
      // By default align to the cache line
      traits default_cardinal {
        force_cardinal<eve::detail::cache_line_cardinal<value_type_t<R>>{}()>
      };

      auto processed = eve::algo::preprocess_range(
        default_to(TraitsSupport::get_traits(), default_cardinal),
        std::forward<R>(r));

      auto f  = processed.begin();
      auto l  = processed.end();

      using I  = decltype(f);

      if ((l - f) <= min_subtask_size) {
        d.first_step(as_range(f, l.unaligned()));
        d.last_step(as_range(l.unaligned(), l.unaligned()));
        return (f != l) ? 1 : 0;
      }

      std::ptrdiff_t step = typename I::cardinal{}();
      std::ptrdiff_t chunk_size = std::max((l - f) / subtask_count, min_subtask_size);
      chunk_size -= chunk_size % step;

      auto f1 = (f.unaligned() + chunk_size + step).previous_partially_aligned();
      d.first_step(as_range(f, f1.unaligned()));

      std::ptrdiff_t count = 2;
      count += (l - f1) / chunk_size;

      while (l - f1 > chunk_size)
      {
        auto f2 = f1 + chunk_size;
        d.step(as_range(f1, f2));
        f1 = f2;
      }

      d.last_step(as_range(f1.unaligned(), l));

      return count;
    }
  };

  inline constexpr auto split_for_parallel_execution = function_with_traits<split_for_parallel_execution_>[no_traits];
}
