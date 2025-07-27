//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/translation.hpp>
#include <eve/memory/pointer.hpp>

#include <concepts>

namespace eve
{
  //==================================================================================================
  //! @concept translatable_ptr
  //! @{
  //! @brief Specify that a type is a scalar pointer to a type that has a plain translation.
  //!
  //! ## Example Types
  //! - `std::byte*`
  //==================================================================================================
  template <typename T>
  concept translatable_ptr = detail::scalar_pointer<T> && has_plain_translation<value_type_t<T>>;
  //==================================================================================================
  //! @}
  //==================================================================================================
}
