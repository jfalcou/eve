//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>

#include <cstddef>
#include <cstdint>

#include <type_traits>

namespace eve
{
namespace detail
{
  template<typename T> struct is_natural : std::false_type {};

  template<typename T>
  requires(std::integral<T> && (sizeof(T) <= 8) && !detail::one_of<T, bool, char>)
  struct is_natural<T> : std::true_type {};

  template<typename T>
  inline constexpr bool is_natural_v = is_natural<T>::value;
}

template<typename T>
concept plain_scalar_value = detail::one_of<T, float, double> || detail::is_natural_v<T>;

namespace detail
{
  template<typename T> constexpr bool scalar_tuple()
  {
    if constexpr( kumi::product_type<T> )
    {
      if constexpr(kumi::size<T>::value != 0)
      {
        using flatten_t = kumi::result::flatten_all_t<T>;
        return []<std::size_t... I>( std::index_sequence<I...> )
        {
          return (plain_scalar_value<kumi::element_t<I,flatten_t>> && ... && true);
        }(std::make_index_sequence<kumi::size<flatten_t>::value>{});
      }
      else
      {
        return false;
      }
    }
    else { return false; }
  }
}

template<typename T>
concept product_scalar_value = detail::scalar_tuple<T>();

template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
