//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
          auto [l, h] = v.slice();
          return eve::all(l && h);
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
        return eve::all(to_logical(v));
      }
    }
  }

  template<simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
         if constexpr ( !is_logical_v<T> ) return eve::all[cond](to_logical(v));
    else if constexpr ( C::is_complete )
    {
      if constexpr ( !C::is_inverted ) return true;
      else                             return eve::all(v);
    }
    else
    {
      bool res = true;

      std::ptrdiff_t first = cond.offset(eve::as_<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as_<T>{});
      while (first != last) res = res && v.get(first++);

      return res;
    }
  }
}
