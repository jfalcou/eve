//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/patterns.hpp>

namespace eve::detail
{
  template<typename T, typename N, arm_abi ABI, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(neon128_), any_pattern const&
                                  , Pattern const& p, wide<T,N,ABI> const& v
                                  )
  {
    constexpr auto sz = Pattern::size(N::value);
    using that_t = wide<T,fixed<sz>>;

    if constexpr( std::same_as<ABI, neon64_> )
    {
      using that_abi_t  = typename that_t::abi_type;
      using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<8>>;
      auto b0 = bit_cast(v,as_<bytes_t>());

      if constexpr( std::same_as<that_abi_t, neon64_> )
      {
        bytes_t that = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(p,as_<bytes_t>()));

        return bit_cast(that,as_<that_t>());
      }
      else
      {
        using out_t = typename that_t::template rebind<std::uint8_t,fixed<16>>;

        auto sp     = pattern_view<sz/2,sz/2>(p);
        bytes_t h   = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(sp,as_<bytes_t>()));
        bytes_t l   = vtbl1_u8(b0,as_bytes<wide<T,N,ABI>>(p,as_<bytes_t>()));

        return bit_cast(out_t{l,h}, as_<that_t>());
      }
    }
    else if constexpr( std::same_as<ABI, neon128_> )
    {
      using bytes_t     = typename that_t::template rebind<std::uint8_t,fixed<16>>;
      bytes_t     b0    = bit_cast(v,as_<bytes_t>());
      uint8x8x2_t lh    = {{ vget_low_u8(b0), vget_high_u8(b0) }};
      auto        mask  = as_bytes<that_t>(p,as_<bytes_t>());

      using that_abi_t  = typename that_t::abi_type;
      if constexpr( std::same_as<that_abi_t, neon64_> )
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
