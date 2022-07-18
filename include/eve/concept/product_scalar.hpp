//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/plain_scalar.hpp>
#include <eve/concept/logical_scalar.hpp>
#include <eve/detail/kumi.hpp>

#include <utility>

namespace eve
{
namespace detail
{
  template<typename T>
  requires( !kumi::product_type<T> )
  static constexpr bool check_scalar() noexcept
  {
    return plain_scalar_value<T> || logical_scalar_value<T>;
  }

  template<typename T>
  requires( kumi::product_type<T> )
  static constexpr bool check_scalar() noexcept
  {
    return []<std::size_t... I>( std::index_sequence<I...> )
    {
      return ( check_scalar<kumi::element_t<I,T>>()&& ... && true );
    }(std::make_index_sequence<kumi::size<T>::value>{});
  }
}

template<typename T>
concept product_scalar_value = detail::check_scalar<T>();
}
