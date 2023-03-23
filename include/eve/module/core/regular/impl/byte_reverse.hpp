//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#include <array>
#include <ranges>
#include <bit>

namespace eve::detail
{
  template<integral_value T>
  EVE_FORCEINLINE auto
  byte_reverse_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      constexpr auto S = sizeof(T);
      if constexpr(S == 1) return x;
      else
      {
        auto b = std::bit_cast<std::array<uint8_t, S>>(x);
        std::ranges::reverse(b.begin(), b.end());
        return std::bit_cast<T>(b);
      }
    }
    else if constexpr(has_native_abi_v<T>)
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      if constexpr(S == 1) return x;
      else
      {
        constexpr auto C = cardinal_v<T>;
        using u8_t = wide<uint8_t, fixed<S*C>>;
        auto p = [] (auto i, auto ) { auto S = sizeof(e_t); return (i/S+1)*S-1-i%S; };
        auto y = eve::shuffle(bit_cast(x, as<u8_t>()), eve::as_pattern(p));
        return bit_cast(y, as<T>());
      }
    }
    else
      return apply_over(byte_reverse, x);
  }

  // Masked case
  template<conditional_expr C, ordered_value U>
  EVE_FORCEINLINE auto
  byte_reverse_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::byte_reverse, t);
  }
}
