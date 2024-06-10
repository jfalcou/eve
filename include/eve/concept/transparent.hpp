//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>
#include <concepts>
#include <bit>

namespace eve
{
  // Default case: normal types do not have specific storage type
  template <typename T>
  struct transparent_trait {
    using type = T;
  };

  template <typename T>
  using transparent_inner_t = typename transparent_trait<T>::type;

  template <typename T>
  concept transparent_value = !std::same_as<transparent_inner_t<T>, T>;

  template <typename V>
  constexpr auto transparent_inner(V val) {
    static_assert((sizeof(V) == sizeof(transparent_inner_t<V>)) && (alignof(V) == alignof(transparent_inner_t<V>)));
    return std::bit_cast<transparent_inner_t<V>>(val);
  }

  // Covers every enum
  template <typename T>
  requires (std::is_enum_v<T>)
  struct transparent_trait<T>: std::underlying_type<T>
  { };
}
