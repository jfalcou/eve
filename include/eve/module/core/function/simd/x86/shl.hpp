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
  EVE_FORCEINLINE wide<T, N, x86_128_> shl_(EVE_SUPPORTS(sse2_),
                                        wide<T, N, x86_128_> const &a0,
                                        I const &               a1) noexcept
  {

    if constexpr(sizeof(T) == 1)
    {
      using r_t = wide<T, N, x86_128_>;
      using N16 = fixed<N::value/2>;
      using i16_t = wide<std::uint16_t, N16>;
      const i16_t masklow(0xff);
      const i16_t maskhi (0xff00);
      auto xx =  bit_cast(a0, as<i16_t>());
      auto odd  = shl(xx, a1)&masklow;
      auto even = shl(xx &maskhi, a1)&maskhi;
      return bit_cast(odd+even, as<r_t>());
    }
    else if constexpr(sizeof(T) == 2)
    {
      return _mm_slli_epi16(a0, a1);
    }
    else if constexpr(sizeof(T) == 4)
    {
      return _mm_slli_epi32(a0, a1);
    }
    else if constexpr(sizeof(T) == 8)
    {
      return _mm_slli_epi64(a0, a1);
    }
  }

  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_>
  shl_(EVE_SUPPORTS(avx_),
       wide<T, N, x86_128_> const &a0,
       wide<I, N, x86_128_> const &a1) noexcept
  {
    if constexpr(supports_xop)
    {
      if constexpr(sizeof(T) == 1)
        return _mm_shl_epi8(a0, a1);
      else if constexpr(sizeof(T) == 2)
        return _mm_shl_epi16(a0, a1);
      else if constexpr(sizeof(T) == 4)
        return _mm_shl_epi32(a0, a1);
      else if constexpr(sizeof(T) == 8)
        return _mm_shl_epi64(a0, a1);
    }
    else
      return map(eve::shl, a0, a1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_>  shl_(EVE_SUPPORTS(avx_),
                                         wide<T, N, x86_256_> const &a0,
                                         I const &               a1) noexcept
  {
    if constexpr(current_api >= avx2)
    {
      if constexpr(sizeof(T) == 1)
      {
        using r_t = wide<T, N, x86_256_>;
        using N16 = fixed<N::value/2>;
        using i16_t = wide<std::uint16_t, N16>;
        const i16_t masklow(0xff);
        const i16_t maskhi (0xff00);
        auto xx =  bit_cast(a0, as<i16_t>());
        auto odd  = shl(xx, a1)&masklow;
        auto even = shl(xx &maskhi, a1)&maskhi;
        return bit_cast(odd+even, as<r_t>());
      }
      else if constexpr(sizeof(T) == 2)
        return _mm256_slli_epi16(a0, a1);
      else if constexpr(sizeof(T) == 4)
        return _mm256_slli_epi32(a0, a1);
      else if constexpr(sizeof(T) == 8)
        return _mm256_slli_epi64(a0, a1);
    }
    else
      return shl_(EVE_RETARGET(sse2_), a0, a1); // map(shl, a0, a1);
  }

  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_>
  shl_(EVE_SUPPORTS(avx_),
       wide<T, N, x86_256_> const &a0,
       wide<I, N, x86_256_> const &a1) noexcept
  {
    [[ maybe_unused ]] auto ifxop_choice = [](const auto &a0, const auto &a1) {
      if constexpr(supports_xop)
        return shl_(EVE_RETARGET(sse2_), a0, a1);
      else
        return map(shl, a0, a1);
    };
    if constexpr(current_api >= avx2)
    {
      if constexpr(sizeof(T) <= 2)
        return ifxop_choice(a0, a1);
      else if constexpr(sizeof(T) == 4)
        return _mm256_sllv_epi32(a0, a1);
      else if constexpr(sizeof(T) == 8)
        return _mm256_sllv_epi64(a0, a1);
    }
    else
      return ifxop_choice(a0, a1);
  }
}
