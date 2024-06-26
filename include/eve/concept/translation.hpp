//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/translation.hpp>

#include <concepts>

namespace eve
{
  //==================================================================================================
  //! @concept has_plain_translation
  //! @brief Specify that a type can be translated to a plain scalar value.
  //! The concept `has_plain_translation<T>` is satisfied if and only if calling `translate_t<T>`
  //! returns a type that is different from `T`.
  //!
  //! ## Example Types
  //! - `std::byte`
  //==================================================================================================
  template <typename T>
  concept has_plain_translation = !std::same_as<translate_t<T>, T>;
}
