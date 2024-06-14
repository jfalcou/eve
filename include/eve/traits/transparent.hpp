//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>

namespace eve
{
  // Default case: normal types do not have specific storage type
  template <typename T>
  struct transparent_trait {
    using type = T;
  };

  template <typename T>
  using transparent_inner_t = typename transparent_trait<T>::type;

  // Covers every enum
  template <typename T>
  requires (std::is_enum_v<T>)
  struct transparent_trait<T>: std::underlying_type<T>
  { };
}
