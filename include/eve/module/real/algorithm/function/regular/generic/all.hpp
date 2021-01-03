//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/to_logical.hpp>

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return bool(v);
    }
    else if constexpr( simd_value<T> )
    {
      if constexpr( is_logical_v<T> )
      {
        if constexpr( has_aggregated_abi_v<T> )
        {
          return v.storage().apply( [](auto const &... e) { return eve::all((e && ...)); } );
        }
        else
        {
          bool r = true;

          [&]<std::size_t... I>(std::index_sequence<I...> const &) { r = (r && ... && get<I>(v)); }
          (std::make_index_sequence<cardinal_v<T>> {});

          return r;
        }
      }
      else
      {
        return all(to_logical(v));
      }
    }
  }
}
