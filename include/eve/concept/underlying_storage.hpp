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

namespace eve
{
  // Default case: normal types do not have specific storage class
  template <typename T>
  struct underlying_storage {
    using type = T;
  };

  template <typename T>
  using underlying_storage_t = typename underlying_storage<T>::type;

  // TODO: add check for sizeof(T) == sizeof(underlying_storage_t<T>) somewhere
  template <typename T>
  concept has_underlying_representation = !std::same_as<underlying_storage_t<T>, T>;

  // Capture every enum by default
  template <typename T>
  requires (std::is_enum_v<T>)
  struct underlying_storage<T>: std::underlying_type<T>
  {
    using eve_disable_ordering = void;
  };
}
