//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/is_wide.hpp>
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
    struct  has_no_loss_conversion
          : std::bool_constant<!(std::is_floating_point_v<T> && std::is_integral_v<U>)>
    {};

    template<typename Dest, typename... Ts>
    constexpr bool is_properly_convertible(types<Ts...> const&) noexcept
    {
      // If the computed destination type is a wide
      // All types must convert to it without impromptu truncation
      if constexpr( is_wide<Dest>::value )
      {
        using type = element_type_t<Dest>;
        bool found[] = { has_no_loss_conversion<element_type_t<Ts>,type>::value... };

        for(auto f : found)
          if(!f) return false;
      }

      return true;
    }
  }

  template<typename... Ts>
  concept compatible
        = detail::is_properly_convertible<common_compatible_t<Ts...>>( detail::types<Ts...>{} );
}
