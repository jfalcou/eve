//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/concept/logical.hpp>

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
  //! @concept scalar_value
  //! @brief Specify that a type represents a scalar value
  //!
  //! The concept `scalar_value<T>` is satisfied if and only if it is arithmetic or a product type
  //! which types satisfies scalar_value themselves.
  //!
  //! @groupheader{Examples}
  //! - `float`
  //! - `std::int32_t`
  //================================================================================================
  template<typename T>
  concept scalar_value = detail::is_scalar_value<T>::value;

  //================================================================================================
  //! @concept integral_scalar_value
  //! @brief Specify that a type represents an integral scalar value
  //!
  //! The concept `integral_scalar_value<T>` is satisfied if and only if T satisfies
  //! `eve::scalar_value<T>` and `std::integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //================================================================================================
  template<typename T>
  concept integral_scalar_value  = scalar_value<T> && std::integral<T>;

  //================================================================================================
  //! @concept signed_scalar_value
  //! @brief Specify that a type represents a signed scalar value
  //!
  //! The concept `signed_scalar_value<T>` is satisfied if and only if T  satisfies
  //! `eve::scalar_value<T>` and `std::integral<T>`.
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //! - `float`
  //================================================================================================
  template<typename T>
  concept signed_scalar_value  = scalar_value<T> && std::is_signed_v<T>;

  //================================================================================================
  //! @concept unsigned_scalar_value
  //! @brief Specify that a type represents a scalar value
  //!
  //! The concept `unsigned_scalar_value<T>` is satisfied if and only if T is unsigned and scalar_value
  //!
  //! @groupheader{Examples}
  //! - `std::uint32_t`
  //================================================================================================
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && std::unsigned_integral<T>;

  //================================================================================================
  //! @concept signed_integral_scalar_value
  //! @brief Specify that a type represents a scalar value
  //!
  //! The concept `unsigned_integral_scalar_value<T>` is satisfied if and only if T is signed,  integral and scalar_value
  //!
  //! @groupheader{Examples}
  //! - `std::int32_t`
  //================================================================================================
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && std::signed_integral<T>;

  //================================================================================================
  //! @concept floating_scalar_value
  //! @brief Specify that a type represents a scalar value
  //!
  //! The concept `floating_scalar_value<T>` is satisfied if and only if T is floating_point and scalar_value
  //!
  //! @groupheader{Examples}
  //! - `float`
  //! - `double`
  //================================================================================================
  template<typename T> concept floating_scalar_value          = scalar_value<T> && std::floating_point<T>;
}
