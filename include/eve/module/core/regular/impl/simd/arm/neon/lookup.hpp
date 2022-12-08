//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/generic/lookup_helpers.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
template<typename T, typename I, typename N>
EVE_FORCEINLINE wide<T, N>
                lookup_(EVE_SUPPORTS(neon128_), wide<T, N> a, wide<I, N> idx) noexcept
    requires(arm_abi<abi_t<I, N>>&& arm_abi<abi_t<T, N>>)
{
  if constexpr( std::is_signed_v<I> )
  {
    using utype = wide<make_integer_t<sizeof(I), unsigned>, N>;
    return lookup(a, bit_cast(idx, as<utype>()));
  }
  else
  {
    if constexpr( std::same_as<abi_t<T, N>, arm_64_> )
    {
      using bytes_t = typename wide<I, N>::template rebind<std::uint8_t, fixed<8>>;
      using tgt_t   = as<bytes_t>;
      auto b        = bit_cast(a, tgt_t {});

      if constexpr( sizeof(I) == 1 && sizeof(T) == 1 )
      {
        return bit_cast(bytes_t {vtbl1_u8(b.storage(), bit_cast(idx, as<bytes_t>()))}, as(a));
      }
      else if constexpr( std::same_as<abi_t<I, N>, arm_64_> )
      {
        using i_t = wide<as_integer_t<T>, N>;
        bytes_t i1 = lookup(bit_cast(idx << shift<T>, tgt_t()), bytes_t {repeater<T, I>});
        i1         = bit_cast(bit_cast(i1, as<i_t()) + i_t{offset<T>}, tgt_t());
        return bit_cast(bytes_t {lookup(b, i1)}, as(a));
      }
      else { return lookup(a, convert(idx, as<as_integer_t<T>>())); }
    }
    else if constexpr( std::same_as<abi_t<T, N>, arm_128_> )
    {
      using bytes_t = typename wide<I, N>::template rebind<std::uint8_t, fixed<16>>;
      using tgt_t   = as<bytes_t>;
      auto b        = bit_cast(a, tgt_t {});

      if constexpr( std::same_as<abi_t<I, N>, arm_64_> )
      {
        // Extend index to the properly sized integer then lookup
        return lookup(a, eve::convert(idx, as<as_integer_t<T>> {}));
      }
      else
      {
        if constexpr( sizeof(I) == 1 && sizeof(T) == 1 )
        {
          if constexpr( current_api >= asimd )
          {
            return bit_cast(vqtbl1q_u8(b, bit_cast(idx, tgt_t())), as(a));
          }
          else
          {
            auto        ba  = bit_cast(a, tgt_t {});
            uint8x8x2_t lhi = {{vget_low_u8(ba), vget_high_u8(ba)}};
            bytes_t     bi =
                vcombine_u8(vtbl2_u8(lhi, vget_low_u8(idx)), vtbl2_u8(lhi, vget_high_u8(idx)));
            return bit_cast(bi, as(a));
          }
        }
        else
        {
          if constexpr( current_api >= asimd )
          {
            bytes_t i1 = vqtbl1q_u8(bit_cast(idx << shift<T>, tgt_t()), bytes_t {repeater<T, I>});
            i1 = bit_cast(bit_cast(i1, as<wide<as_integer_t<T>, N>>()) + offset<T>, tgt_t());
            return bit_cast(vqtbl1q_u8(b, i1), as(a));
          }
          else
          {
            auto    bi = lookup(bit_cast(idx << shift<T>, tgt_t()), bytes_t {repeater<T, I>});
            bytes_t i1 =
                bit_cast(bit_cast(bi, as<wide<as_integer_t<T>, N>>()) + offset<T>, tgt_t());
            return bit_cast(lookup(b, i1), as(a));
          }
        }
      }
    }
  }
}
}
