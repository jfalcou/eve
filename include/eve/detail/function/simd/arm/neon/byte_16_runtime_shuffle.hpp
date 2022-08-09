//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template <typename N>
  EVE_FORCEINLINE
  wide<std::uint8_t, N> byte_16_runtime_shuffle_(EVE_SUPPORTS(neon128_)
                                               , wide<std::uint8_t, N> what
                                               , wide<std::uint8_t, N> pattern) noexcept
    requires ( N() <= 16 )
  {
         if constexpr ( N() <= 8                       ) return vtbl1_u8  (what, pattern);
    else if constexpr ( eve::current_api == eve::asimd ) return vqtbl1q_u8(what, pattern);
    else
    {
      uint8x8x2_t lh  = {{ vget_low_u8(what), vget_high_u8(what) }};
      return vcombine_u8(
        vtbl2_u8(lh, vget_low_u8(pattern)), vtbl2_u8(lh, vget_high_u8(pattern))
      );
    }
  }
}
