//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/traits/element_type.hpp>

#include <type_traits>

namespace eve
{
namespace detail
{
  // Note: this traits is customizable for other types we may need later on (complex,etc...)
  template<typename T, typename U>
  struct has_no_loss_convertion
      : std::bool_constant<!(std::is_floating_point_v<T> && std::is_integral_v<U>)>
  {};

  template<typename Dest, typename... Ts>
  constexpr bool is_properly_convertible(types<Ts...> const&) noexcept
  {
    // If the computed destination type is a wide
    // All types must convert to it without impromptu truncation
    if constexpr( simd_value<Dest> )
    {
      using type   = element_type_t<Dest>;
      bool found[] = {has_no_loss_convertion<Ts, type>::value...};

      for( auto f : found )
        if( !f ) return false;
    }

    return true;
  }
}

template<typename... Ts>
concept properly_convertible =
    detail::is_properly_convertible<common_compatible_t<Ts...>>(detail::types<Ts...> {});
}
