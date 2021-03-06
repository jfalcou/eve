//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <concepts>
#include <iterator>
#include <type_traits>
#include <eve/function/load.hpp>

namespace eve::algo
{
  namespace detail
  {
    template <typename>
    struct is_fixed  : std::false_type {};

    template <std::ptrdiff_t N>
    struct is_fixed<eve::fixed<N>> : std::true_type {};

    template <typename T>
    concept is_fixed_v = is_fixed<T>::value;
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
    detail::is_fixed_v<typename I::cardinal> &&
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

  namespace detail
  {
    template <typename T, template <typename ...> class Templ>
    struct instance_of_impl : std::false_type {};

    template <typename ...Args, template <typename ...> class Templ>
    struct instance_of_impl<Templ<Args...>, Templ> : std::true_type {};
  }

  template <typename T, template <typename ...> class Templ>
  concept instance_of = detail::instance_of_impl<T, Templ>::value;

  // While standard ranges are not properly supported
  namespace detail
  {
    template<typename R>
    concept contiguous_range = std::contiguous_iterator<decltype(std::declval<R>().begin())>;
  }
}
