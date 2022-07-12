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
  requires(std::integral<T> && (sizeof(T) <= 8) && !std::same_as<T,bool> && !std::same_as<T,char>)
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
      return kumi::size_v<T> ? kumi::all_of(kumi::flatten_all(kumi::as_tuple_t<T> {}),
                                            []<typename M>(M) { return plain_scalar_value<M>; })
                             : false;
    }
    else { return false; }
  }
}

template<typename T>
concept product_scalar_value = detail::scalar_tuple<T>();

template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
