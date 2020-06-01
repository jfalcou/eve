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
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> rotl_(EVE_SUPPORTS(avx_),
                                        wide<T, N, sse_> const &a0,
                                        I const &               a1) noexcept
  {
    if constexpr(supports_xop)
    {
      if constexpr(sizeof(T) == 8) return _mm_rot_epi64(a0,a1);
      else if constexpr(sizeof(T) == 4) return _mm_rot_epi32(a0,a1);
      else if constexpr(sizeof(T) == 2) return _mm_rot_epi16(a0,a1);
      else if constexpr(sizeof(T) == 1) return _mm_rot_epi8(a0,a1);
    }
    else
    {
      return rotl_(EVE_RETARGET(cpu_), a0, a1);
    }
  }

}

