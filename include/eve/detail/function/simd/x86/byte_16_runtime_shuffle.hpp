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
  wide<std::uint8_t, N> byte_16_runtime_shuffle_(EVE_SUPPORTS(ssse3_)
                                               , wide<std::uint8_t, N> what
                                               , wide<std::uint8_t, N> pattern) noexcept
    requires ( N() <= 16 )
  {
    return _mm_shuffle_epi8(what, pattern);
  }
}
