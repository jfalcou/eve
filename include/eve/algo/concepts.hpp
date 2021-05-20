//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <concepts>
#include <type_traits>
#include <eve/function/load.hpp>

namespace eve::algo
{
  namespace detail
  {
    template <typename>
    struct is_eve_fixed  : std::false_type {};

    template <std::ptrdiff_t N>
    struct is_eve_fixed<eve::fixed<N>> : std::true_type {};

    template <typename T>
    concept is_eve_fixed_v = is_eve_fixed<T>::value;
  }

  template <typename T>
  using unaligned_t = decltype(std::declval<T>().unaligned());

  // Do the other way around to the normal one, otherwise there is a compilation issue.
  template <typename T>
  struct unaligned
  {
    using type = unaligned_t<T>;
  };

  template <typename T>
  using partialy_unaligned_t = decltype(std::declval<T>().previous_partially_aligned());

  template <typename I>
  concept unaligned_check = std::same_as<unaligned_t<I>, I>;

  template <typename I>
  concept partially_aligned_check = std::same_as<partialy_unaligned_t<I>, I>;

  template <typename I>
  concept iterator_basics =
    detail::is_eve_fixed_v<typename I::cardinal> &&
    std::regular<I> &&
    std::totally_ordered<I> &&
    std::totally_ordered_with<I, unaligned_t<I>> &&
    std::totally_ordered_with<I, partialy_unaligned_t<I>> &&
    requires(I i, std::ptrdiff_t n) {
       { i += n } -> std::same_as<I&>;
       { i - i }  -> std::same_as<std::ptrdiff_t>;
       { i.unaligned() } -> unaligned_check;
       { i.previous_partially_aligned() } -> partially_aligned_check;
    };

  template <typename I>
  concept readable_iterator = iterator_basics<I> &&
    requires(I i) {
      { eve::load(i) };
      { eve::load[eve::ignore_first(1)](i) };
      { eve::load[eve::ignore_extrema(1, 0)](i) };
    };

  template <typename I>
  concept unaligned_iterator = iterator_basics<I> && unaligned_check<I>;

  template <typename I>
  concept partially_aligned_iterator = iterator_basics<I> && partially_aligned_check<I>;


  template <typename S, typename I>
  concept sentinel_for = std::totally_ordered_with<S, I> &&
    requires(I i, S s) {
      { s - i } -> std::same_as<std::ptrdiff_t>;
    };


  template <typename T, typename U>
  concept same_unaligned_iterator = std::same_as<unaligned_t<T>, unaligned_t<U>>;
}
