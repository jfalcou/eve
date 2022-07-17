//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/meta.hpp>
#include <compare>
#include <concepts>
#include <type_traits>

namespace eve::algo::detail
{
  template <typename R>
  concept has_begin_end = requires (R&& r) {
      { r.begin() };
      { r.end() };
  };

  template <typename T, typename U>
  concept supports_spaceship = requires (T x, U y) {
    { std::declval<T>() <=> std::declval<U>() };
  };

  template <typename>
  struct is_fixed  : std::false_type {};

  template <std::ptrdiff_t N>
  struct is_fixed<eve::fixed<N>> : std::true_type {};

  template <typename T>
  concept is_fixed_v = is_fixed<T>::value;

  template <typename I>
  concept iterator_operations =
    std::copyable<std::remove_cvref_t<I>> &&
    std::totally_ordered<std::remove_cvref_t<I>> &&
    requires(std::remove_cvref_t<I> f, std::remove_cvref_t<I> l, std::ptrdiff_t n) {
      { l - f }  -> std::convertible_to<std::ptrdiff_t>;
      { f += n } -> std::same_as<std::remove_cvref_t<I>&>;
      { f + n } -> std::same_as<std::remove_cvref_t<I>>;
      { n + f } -> std::same_as<std::remove_cvref_t<I>>;
      { unalign(f) };
    };
}
