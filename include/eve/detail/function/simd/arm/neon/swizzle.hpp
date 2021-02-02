//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/simd/common/swizzle_helpers.hpp>
#include <eve/detail/function/simd/arm/neon/swizzle_patterns.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<typename T, typename N, arm_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle(neon128_ const&, wide<T,N,ABI> const& v, Pattern const&)
  {
    constexpr auto sz = Pattern::size(N::value);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr auto q = as_pattern<N::value>(Pattern{});

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,q);
    }
    // Check for patterns
    else if constexpr( !std::same_as<void, decltype(swizzle_pattern(neon128_{},v,q))> )
    {
      return swizzle_pattern(neon128_{},v,q);
    }
    else
    {
      if constexpr( std::same_as<ABI, arm_64_> )
      {
        using that_abi_t  = typename that_t::abi_type;
        using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<8>>;
        auto b0 = bit_cast(v,as_<bytes_t>());

        if constexpr( std::same_as<that_abi_t, arm_64_> )
        {
          bytes_t that = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(q,as_<bytes_t>()));
          return bit_cast(that,as_<that_t>());
        }
        else
        {
          using out_t = typename that_t::template rebind<std::uint8_t,fixed<16>>;

          auto sp     = pattern_view<sz/2,sz,sz/2>(q);
          bytes_t h   = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(sp,as_<bytes_t>()));
          bytes_t l   = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(q,as_<bytes_t>()));

          return bit_cast(out_t{l,h}, as_<that_t>());
        }
      }
      else if constexpr( std::same_as<ABI, arm_128_> )
      {
        using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<16>>;
        bytes_t     b0    = bit_cast(v,as_<bytes_t>());
        uint8x8x2_t lh    = {{ vget_low_u8(b0), vget_high_u8(b0) }};
        auto        mask  = as_bytes<that_t>(q,as_<bytes_t>());

        using that_abi_t  = typename that_t::abi_type;
        if constexpr( std::same_as<that_abi_t, arm_64_> )
        {
          using out_t       = typename that_t::template rebind<std::uint8_t,fixed<8>>;
          return bit_cast(out_t{vtbl2_u8(lh, vget_low_u8 (mask))},as_<that_t>());
        }
        else
        {
          bytes_t that  = vcombine_u8 ( vtbl2_u8(lh, vget_low_u8 (mask))
                                      , vtbl2_u8(lh, vget_high_u8(mask))
                                      );
          return bit_cast(that,as_<that_t>());
        }
      }
    }
  }
}
