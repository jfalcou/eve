//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/plain_scalar.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  template<typename Type> struct logical;

  //================================================================================================
  //! @concept logical_scalar_value
  //! @brief Specify that a type represents a logical scalar value
  //!
  //! The concept `logical_scalar_value<T>` is satisfied if and only if T is an instance of
  //! eve::logical and its contents satisfy eve::plain_scalar_value
  //!
  //! ## Example Types
  //! - `logical<float>`
  //! - `logical<int>`
  //================================================================================================
  template<typename T>
  concept logical_scalar_value  =   detail::instance_of<T,logical>
                                &&  plain_scalar_value<typename T::value_type>;
}
