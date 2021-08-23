//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/is_logical.hpp>

#include <concepts>
#include <type_traits>
#include <utility>

namespace eve::detail
{
  //================================================================================================
  // Check if something is a scalar_value
  //================================================================================================

  //================================================================================================
  // Case #1 - it is arithmetic
  //================================================================================================
  template<typename T> struct is_scalar_value : std::is_arithmetic<T>
  {};

  //================================================================================================
  // Case #2 - it is a product_type of arithmetic
  //================================================================================================
  template<typename T>
  static constexpr bool check_tuple()
  {
    return []<std::size_t... I>( std::index_sequence<I...> )
    {
      return ( is_scalar_value<kumi::element_t<I,T>>::value && ... && true );
    }(std::make_index_sequence<kumi::size<T>::value>{});
  }

  template<typename T>
  requires( kumi::product_type<T> )
  struct  is_scalar_value<T> : std::bool_constant< check_tuple<T>() >
  {};

  //================================================================================================
  // Case #3 - it is a logical
  //================================================================================================
  template<typename T>
  struct is_scalar_value<eve::logical<T>> : std::is_arithmetic<T>
  {};
}

namespace eve
{
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var scalar_value
  //! The concept `scalar_value<T>` is satisfied if and only if it is arithmetic or a product type
  //!
  //! #### Examples
  //! - `float`
  //! - `std::int32_t`
  //! @}
  //================================================================================================
  template<typename T> concept scalar_value                   = detail::is_scalar_value<T>::value;

  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var integral_scalar_value
  //! The concept `integral_scalar_value<T>` is satisfied if and only if T is integral and scalar_value
  //!
  //! #### Examples
  //! - `std::int32_t`
  //! @}
  //================================================================================================
  template<typename T> concept integral_scalar_value          = scalar_value<T> && std::integral<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var signed_scalar_value
  //! The concept `signed_scalar_value<T>` is satisfied if and only if T is signed and scalar_value
  //!
  //! #### Examples
  //! - `std::int32_t`
  //! - `float`
  //! @}
  //================================================================================================
  template<typename T> concept signed_scalar_value            = scalar_value<T> && std::is_signed_v<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var unsigned_scalar_value
  //! The concept `unsigned_scalar_value<T>` is satisfied if and only if T is unsigned and scalar_value
  //!
  //! #### Examples
  //! - `std::uint32_t`
  //! @}
  //================================================================================================
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && std::unsigned_integral<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var signed_integral_scalar_value
  //! The concept `unsigned_integral_scalar_value<T>` is satisfied if and only if T is signed,  integral and scalar_value
  //!
  //! #### Examples
  //! - `std::int32_t`
  //! @}
  //================================================================================================
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && std::signed_integral<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var floating_scalar_value
  //! The concept `floating_scalar_value<T>` is satisfied if and only if T is floating_point and scalar_value
  //!
  //! #### Examples
  //! - `float`
  //! - `double`
  //! @}
  //================================================================================================
  template<typename T> concept floating_scalar_value          = scalar_value<T> && std::floating_point<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var logical_scalar_value
  //! The concept `logical_scalar_value<T>` is satisfied if and only if T is logical and scalar_value
  //!
  //! #### Examples
  //! - `logical<float>`
  //! - `logical<int>`
  //! @}
  //================================================================================================
  template<typename T> concept logical_scalar_value           = scalar_value<T> && is_logical_v<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var real_scalar_value
  //! The concept `real_scalar_value<T>` is satisfied if and only if T is scalar_value and real_value
  //!
  //! #### Examples
  //! - `float`
  //! - `int`
  //! @}
  //================================================================================================
  template<typename T> concept real_scalar_value              = scalar_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var floating_real_scalar_value
  //! The concept `floating_real_scalar_value<T>` is satisfied if and only if T is scalar_value and floating_real_value
  //!
  //! #### Examples
  //! - `float`
  //! - `double`
  //! @}
  //================================================================================================
  template<typename T> concept floating_real_scalar_value     = real_scalar_value<T> && std::floating_point<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var integral_real_scalar_value
  //! The concept `integral_real_scalar_value<T>` is satisfied if and only if T is scalar_value and integral_real_value
  //!
  //! #### Examples
  //! - `int`
  //! - `unsigned int`
  //! @}
  //================================================================================================
  template<typename T> concept integral_real_scalar_value     = real_scalar_value<T> && std::integral<detail::value_type_t<T>>;
}
