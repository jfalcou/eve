//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
template<typename T>
concept   plain_scalar_value
        =  !(std::is_same_v<T, bool> || std::is_same_v<T, long double>)
        &&  (std::is_floating_point_v<T> || std::is_integral_v<T>);

namespace detail
{
  template<typename T>
  constexpr bool scalar_tuple()
  {
    if constexpr(!kumi::product_type<T>) return false;
    else
    {
      constexpr auto f = []<typename M>(M) { return std::bool_constant<plain_scalar_value<M>>{}; };
      using flt_t = kumi::result::flatten_all_t<kumi::as_tuple_t<T>, decltype(f)>;
      return  kumi::all_of( flt_t{}, [](bool b) { return b; } );
    }
  }
}

template<typename T>
concept product_scalar_value = detail::scalar_tuple<T>();

template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
