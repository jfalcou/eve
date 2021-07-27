//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
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
  template<typename T> concept scalar_value                   = detail::is_scalar_value<T>::value;

  template<typename T> concept integral_scalar_value          = scalar_value<T> && std::integral<T>;
  template<typename T> concept signed_scalar_value            = scalar_value<T> && std::is_signed_v<T>;
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && std::unsigned_integral<T>;
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && std::signed_integral<T>;
  template<typename T> concept floating_scalar_value          = scalar_value<T> && std::floating_point<T>;
  template<typename T> concept logical_scalar_value           = scalar_value<T> && is_logical_v<T>;
  template<typename T> concept real_scalar_value              = scalar_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;
  template<typename T> concept floating_real_scalar_value     = real_scalar_value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept integral_real_scalar_value     = real_scalar_value<T> && std::integral<detail::value_type_t<T>>;
}
