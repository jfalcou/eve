//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <concepts>
#include <iterator>
#include <type_traits>
#include <eve/function/read.hpp>
#include <eve/function/write.hpp>
#include <eve/function/load.hpp>
#include <eve/function/compress_store.hpp>

#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/unalign.hpp>

namespace eve::algo
{
  template <typename T>
  using partially_aligned_t = decltype(std::declval<T>().previous_partially_aligned());

  template <typename T>
  struct partially_aligned
  {
    using type = partially_aligned_t<T>;
  };

  namespace detail
  {
    template <typename I>
    concept unaligned_check = std::same_as<unaligned_t<I>, I>;

    template <typename I>
    concept partially_aligned_check = std::same_as<partially_aligned_t<I>, I>;
  }

   template <typename I>
  concept iterator =
    requires(I) {
      { I::iterator_cardinal() } -> detail::is_fixed_v;
      typename I::value_type;
    } &&
    std::regular<I> &&
    std::totally_ordered<I> &&
    std::totally_ordered_with<I, unaligned_t<I>> &&
    std::totally_ordered_with<I, partially_aligned_t<I>> &&
    requires(I i, std::ptrdiff_t n) {
       { i += n } -> std::same_as<I&>;
       { i - i }  -> std::same_as<std::ptrdiff_t>;
       { i.unaligned() } -> detail::unaligned_check;
       { i.previous_partially_aligned() } -> detail::partially_aligned_check;
    };

  template <typename I>
  concept readable_iterator = iterator<I> &&
    requires(I i) {
      { eve::read(i) };
      { eve::load(i) };
      { eve::load[eve::ignore_first(1)](i) };
      { eve::load[eve::ignore_extrema(1, 0)](i) };
    };

  template <typename I>
  concept unaligned_iterator = iterator<I> && detail::unaligned_check<I>;

  template <typename I>
  concept partially_aligned_iterator = iterator<I> && detail::partially_aligned_check<I>;

  // We don't yet have examples;
  template <typename I>
  concept always_aligned_iterator = partially_aligned_iterator<I> && unaligned_iterator<I>;

  template <typename S, typename I>
  concept sentinel_for = iterator<I> && std::totally_ordered_with<S, I> &&
    requires(I i, S s) {
      { s - i } -> std::same_as<std::ptrdiff_t>;
    };

  template <typename T, typename U>
  concept same_unaligned_iterator = std::same_as<unaligned_t<T>, unaligned_t<U>>;
}
