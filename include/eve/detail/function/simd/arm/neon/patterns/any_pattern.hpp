//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/patterns.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(neon128_), any_match const&
                                  , as_<Target>     , Pattern const& p, Wide const& v
                                  )
  {
    using abi_t = typename Wide::abi_type;
    constexpr auto sz = Target::static_size;

    if constexpr( std::same_as<abi_t, arm_64_> )
    {
      using that_abi_t  = typename Target::abi_type;
      using bytes_t     = typename Target::template rebind<std::uint8_t,fixed<8>>;
      auto b0 = bit_cast(v,as_<bytes_t>());

      if constexpr( std::same_as<that_abi_t, arm_64_> )
      {
        bytes_t that = vtbl1_u8(b0,as_bytes<Wide>(p,as_<bytes_t>()));

        return bit_cast(that,as_<Target>());
      }
      else
      {
        using out_t = typename Target::template rebind<std::uint8_t,fixed<16>>;

        auto sp     = pattern_view<sz/2,sz/2>(p);
        bytes_t h   = vtbl1_u8(b0,as_bytes<Wide>(sp,as_<bytes_t>()));
        bytes_t l   = vtbl1_u8(b0,as_bytes<Wide>(p,as_<bytes_t>()));

        return bit_cast(out_t{l,h}, as_<Target>());
      }
    }
    else if constexpr( std::same_as<abi_t, arm_128_> )
    {
      using bytes_t     = typename Target::template rebind<std::uint8_t,fixed<16>>;
      bytes_t     b0    = bit_cast(v,as_<bytes_t>());
      uint8x8x2_t lh    = {{ vget_low_u8(b0), vget_high_u8(b0) }};
      auto        mask  = as_bytes<Target>(p,as_<bytes_t>());

      using that_abi_t  = typename Target::abi_type;
      if constexpr( std::same_as<that_abi_t, arm_64_> )
      {
        using out_t       = typename Target::template rebind<std::uint8_t,fixed<8>>;
        return bit_cast(out_t{vtbl2_u8(lh, vget_low_u8 (mask))},as_<Target>());
      }
      else
      {
        bytes_t that  = vcombine_u8 ( vtbl2_u8(lh, vget_low_u8 (mask))
                                    , vtbl2_u8(lh, vget_high_u8(mask))
                                    );
        return bit_cast(that,as_<Target>());
      }
    }
  }
}
