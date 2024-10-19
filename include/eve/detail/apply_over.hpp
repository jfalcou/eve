//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // N parameters apply_over
  template<typename Obj, value T0, value... T>
  EVE_FORCEINLINE auto apply_over(Obj f, T0 const& arg0, T const&... args) noexcept
    requires simd_value<T0> || (simd_value<T> || ...)
  {
    constexpr bool any_aggregated = has_aggregated_abi_v<T0> || (has_aggregated_abi_v<T> || ...);
    constexpr bool any_emulated   = has_emulated_abi_v<T0>   || (has_emulated_abi_v<T>   || ...);

    if      constexpr(any_aggregated) return aggregate(f, arg0, args...);
    else if constexpr(any_emulated)
    {
      using r_e = decltype(f(std::declval<element_type_t<T0>>(), std::declval<element_type_t<T>>()...));
      using r_t = as_wide_as_t<r_e, fixed<std::max({cardinal_t<T0>{}, cardinal_t<T>{}...})>>;
      return map_pt(as<r_t>{}, f, arg0, args...);
    }
    else                              return f(arg0, args...);
  }

  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over(Obj f, T const& v)
  {
    if      constexpr(has_aggregated_abi_v<T>) return aggregate(f, v);
    else if constexpr(has_emulated_abi_v<T>)   return map_pt(as<decltype(f(std::declval<element_type_t<T>>()))>{}, f, v);
    else                                       return f(v);
  }
}
