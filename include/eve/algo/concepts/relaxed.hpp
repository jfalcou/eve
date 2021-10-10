//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/detail/preprocess_range.hpp>
#include <eve/algo/unalign.hpp>

#include <concepts>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!  @struct relaxed_iterator
  //!  @brief anything that can be reasonably converted to an `iterator`:
  //!         std::contigious_iterator, eve::algo::iterator, aligned_ptr.
  //!         Defined as being totally_ordered, having +/- like an iterator
  //!         And `preprocess_range(eve::algo::traits{}, I, I)` should work.
  //!         `eve::algo::unalign(I)` should be OK.
  //!
  //!         +/- with std::ptrdiff_t don't have to work for arbitrary N,
  //!         behaviour along the lines of `eve::aligned_ptr` is sufficient.
  //!
  //!         result of `eve::algo::unalign(I)` should return an iterator that can
  //!         represent any position.
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //! @}
  //================================================================================================

  template <typename I>
  concept relaxed_iterator =
    detail::iterator_operations<I> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, I>;

  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!  @struct relaxed_sentinel_for
  //!  @brief Two relaxed iterators form a valid relaxed range pair.
  //!         `preprocess_range` has to be defined for the pair.
  //!         Example: int const* is a `relaxed_sentinel_for` `aligned_ptr<int const>`.
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //! @}
  //================================================================================================

  template <typename S, typename I>
  concept relaxed_sentinel_for =
    relaxed_iterator<I> &&
    relaxed_iterator<S> &&
    std::totally_ordered_with<I, S> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), I, S> &&
    requires (I f, S l) {
      { l - f } -> std::same_as<std::ptrdiff_t>;
    };

  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!  @struct relaxed_range
  //!  @brief Any class that has `begin/end` and `end` is a `relaxed_sentinel_for` begin.
  //!         User can customize `preprocess_range` for a `relaxed_range` in case there is more
  //!         information to get from there then would be from just `begin`/`end`.
  //!
  //!         Example: `soa_vector::begin` is `unaligned` but the `preprocess_range` returns `aligned`.
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //! @}
  //================================================================================================

  template <typename R>
  concept relaxed_range =
    detail::has_begin_end<R> &&
    relaxed_sentinel_for<decltype(std::declval<R>().end()),
                         decltype(std::declval<R>().begin())> &&
    std::invocable<preprocess_range_, decltype(eve::algo::traits{}), R>;
}
