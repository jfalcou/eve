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
  struct translation_of
  {
    using type = T;
  };

  template <typename T>
  struct recursive_translate
  {
    using type = T;
  };

  template <typename T>
  requires (!std::is_same_v<typename translation_of<T>::type, T>)
  struct recursive_translate<T>: recursive_translate<typename translation_of<T>::type>
  { };

  // Recursively translate the type `T` until `translation_of<T>` is `T`
  template <typename T>
  using translate_t = typename recursive_translate<T>::type;
  
  // Covers every enum
  template <typename T>
  requires (std::is_enum_v<T>)
  struct translation_of<T>: std::underlying_type<T>
  { };
}
