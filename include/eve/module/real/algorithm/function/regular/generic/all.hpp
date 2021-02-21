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
#include <eve/detail/top_bits.hpp>

namespace eve::detail
{
  template<simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
         if constexpr ( !is_logical_v<T> ) return eve::all[cond](to_logical(v));
    else if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( has_emulated_abi_v<T> )
    {
      bool res = true;

      std::ptrdiff_t first = cond.offset(eve::as_<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as_<T>{});
      while (first != last) res = res && v.get(first++);

      return res;
    }
    else if constexpr ( has_aggregated_abi_v<T> && C::is_complete )
    {
      auto [l, h] = v.slice();
      return eve::all[ignore_none](l && h);
    }
    else
    {
      top_bits mmask{v};
      top_bits<T> ignore_mmask{cond};

      mmask |= ~ignore_mmask; // we need 1 in ignored elements;

      return detail::all(mmask);
    }
  }

  template<value T> EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr( scalar_value<T> ) return bool(v);
    else                            return eve::all[ignore_none](v);
  }

}
