//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/func/simd/common/swizzle_helpers.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_shuffle_( EVE_SUPPORTS(neon128_), wide<T,N> const& v, Pattern const&)
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<wide<T,N>,fixed<sz>>;

    constexpr Pattern q = {};

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_shuffler(v,q);
    }
    else
    {
      if constexpr( std::same_as<abi_t<T, N>, arm_64_> )
      {
        using that_abi_t  = typename that_t::abi_type;
        using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<8>>;
        auto b0 = bit_cast(v,as<bytes_t>());

        if constexpr( std::same_as<that_abi_t, arm_64_> )
        {
          bytes_t that = vtbl1_u8(b0,as_bytes<wide<T,N>>(q,as<bytes_t>()));
          return bit_cast(that,as<that_t>());
        }
        else
        {
          using out_t = typename that_t::template rebind<std::uint8_t,fixed<16>>;

          auto sp     = pattern_view<sz/2,sz,sz/2>(q);
          bytes_t h   = vtbl1_u8(b0,as_bytes<wide<T,N>>(sp,as<bytes_t>()));
          bytes_t l   = vtbl1_u8(b0,as_bytes<wide<T,N>>(q,as<bytes_t>()));

          return bit_cast(out_t{l,h}, as<that_t>());
        }
      }
      else if constexpr( std::same_as<abi_t<T, N>, arm_128_> )
      {
        using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<16>>;
        bytes_t     b0    = bit_cast(v,as<bytes_t>());
        auto        mask  = as_bytes<that_t>(q,as<bytes_t>());

        using that_abi_t  = typename that_t::abi_type;
        if constexpr( std::same_as<that_abi_t, arm_64_> )
        {
          using out_t       = typename that_t::template rebind<std::uint8_t,fixed<8>>;
          uint8x8x2_t lh    = {{ vget_low_u8(b0), vget_high_u8(b0) }};
          return bit_cast(out_t{vtbl2_u8(lh, vget_low_u8 (mask))},as<that_t>());
        }
        else
        {
          if constexpr(current_api >= asimd)
          {
            return bit_cast(vqtbl1q_u8(b0, mask),as<that_t>());
          }
          else
          {
            uint8x8x2_t lh  = {{ vget_low_u8(b0), vget_high_u8(b0) }};
            bytes_t that    = vcombine_u8 ( vtbl2_u8(lh, vget_low_u8 (mask))
                                          , vtbl2_u8(lh, vget_high_u8(mask))
                                          );

            return bit_cast(that,as<that_t>());
          }
        }
      }
    }
  }
}
