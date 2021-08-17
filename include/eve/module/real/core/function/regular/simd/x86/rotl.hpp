//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N> rotl_(EVE_SUPPORTS(avx_), wide<T, N> a0, I a1) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_> && supports_xop
  {
           if constexpr(sizeof(T) == 8) return _mm_rot_epi64(a0,a1);
      else if constexpr(sizeof(T) == 4) return _mm_rot_epi32(a0,a1);
      else if constexpr(sizeof(T) == 2) return _mm_rot_epi16(a0,a1);
      else if constexpr(sizeof(T) == 1) return _mm_rot_epi8(a0,a1);
  }
}
