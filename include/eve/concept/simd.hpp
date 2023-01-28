//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/element_type.hpp>

namespace eve
{
  inline namespace EVE_ABI_NAMESPACE
  {
    template<arithmetic_scalar_value Type, typename Size> struct wide;
  }

  template<typename T>
  concept arithmetic_simd_value = detail::instance_of<T,wide>;

  template<typename T>
  concept plain_simd_value =  arithmetic_simd_value<T> && plain_scalar_value<element_type_t<T>>;

  template<typename T>
  concept product_simd_value = arithmetic_simd_value<T> && kumi::product_type<element_type_t<T>>;

  template<typename Type> struct logical;

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
