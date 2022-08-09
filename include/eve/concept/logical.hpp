//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/scalar.hpp>
#include <eve/concept/simd.hpp>
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

  //================================================================================================
  //! @concept logical_simd_value
  //! @brief Specify that a type represents a logical SIMD value
  //!
  //! The concept `logical_simd_value<T>` is satisfied if and only if T is an instance of
  //! eve::logical and its contents satisfy eve::plain_simd_value
  //!
  //! ## Example Types
  //! - eve::logical<eve::wide<float>>
  //! - eve::logical<eve::wide<int,eve::fixed<2>>>
  //================================================================================================
  template<typename T>
  concept logical_simd_value  =   detail::instance_of<T,logical>
                              &&  plain_simd_value<typename T::mask_type>;
}
