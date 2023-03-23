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
#include <eve/module/core/regular/load.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>
#include <eve/module/core/regular/load.hpp>
#include <eve/module/core/regular/store.hpp>
#include <bit>


namespace eve::detail
{
    template<integral_value T>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), T x) noexcept;

  template<integral_value T>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using e_t =  element_type_t<T>;
    constexpr auto S = sizeof(e_t);
    if constexpr(scalar_value<T>)
    {
      wide<T, fixed<1>> w(x);
      return bit_reverse(w).get(0);
    }
    else if constexpr(has_native_abi_v<T>)
    {
      if constexpr(S == 1)
      {
        constexpr uint8_t m1 = 0x55;
        x =  ((x & m1) << 1) | ((x & (bit_not(m1))) >> 1);
        constexpr uint8_t m2 = 0x33;
        x =  ((x & m2) << 2) | ((x & (bit_not(m2))) >> 2);
        constexpr uint8_t m3 = 0x0f;
        x =  ((x & m3) << 4) | ((x & (bit_not(m3))) >> 4);
        return x;
      }
      else
      {
        using u8_t = wide<uint8_t, fixed<S*cardinal_v<T>>>;
        auto z = eve::bit_cast(x, as<u8_t>());
        return byte_reverse( bit_cast(bit_reverse(z), as<T>()));
      }
    }
    else
      return apply_over(bit_reverse, x);
  }

  // Masked case
  template<conditional_expr C, ordered_value U>
  EVE_FORCEINLINE auto
  bit_reverse_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::bit_reverse, t);
  }
}
