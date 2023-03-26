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
#include <eve/detail/builtin_detect.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#include <array>
#include <algorithm>
#include <bit>

namespace eve::detail
{
  template<unsigned_scalar_value T>
  T bswap(T x)
  {
    constexpr size_t S = sizeof(T);
    auto bs=[](auto x){
      auto b = std::bit_cast<std::array<std::uint8_t, S>>(x);
      std::reverse(b.begin(), b.end());
      return std::bit_cast<T>(b);
    };
    if constexpr(sizeof(T)==1)
    {
      return x;
    }
    else    if constexpr(sizeof(T)==2)
    {
      return bit_shl(x, 8) | bit_shr(x, 8);
    }
    else if constexpr(sizeof(T)==8)
    {
      if constexpr(has_builtin_swap64())
      {
        if constexpr(spy::compiler==spy::msvc_) return _byteswap_uint64(x);
        else return __builtin_bswap64(x);
      }
      else return bs(x);
    }
    else    if constexpr(sizeof(T)==4)
    {
      if constexpr(has_builtin_swap32())
      {
        if constexpr(spy::compiler==spy::msvc_) return _byteswap_ulong(x);
        else return __builtin_bswap632(x);
      }
      else return bs(x);
    }
  }

  template<integral_value T>
  EVE_FORCEINLINE auto
  byte_reverse_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      using u_t = as_uinteger_t<T>;
      return std::bit_cast<T>(bswap(std::bit_cast<u_t>(x)));
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
        x = bit_cast(y, as<T>());
        return x;
      }
    }
    else
      return apply_over(byte_reverse, x);
  }

  // Masked case
  template<conditional_expr C, integral_value U>
  EVE_FORCEINLINE auto
  byte_reverse_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::byte_reverse, t);
  }
}
