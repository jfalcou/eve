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
  EVE_FORCEINLINE wide<T, N, sse_> shr_(EVE_SUPPORTS(sse2_)
                                       , wide<T, N, sse_> const &a0, I const & a1) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
// waiting for shuffles
//      if constexpr(supports_avx)
//         {
//           auto x16 = _mm256_cvtepu8_epi16(a0);
//           auto tmp = shr(x16, a1);
//           return //shuffle tmp to a 128bits of low parts
//         }
//         else
         {
          using r_t = wide<T, N, sse_>;
          using N16 = fixed<N::value/2>;
          using i16_t = wide<std::uint16_t, N16>;
          const i16_t masklow(0xff);
          const i16_t maskhi (0xff00);
          auto xx =  bit_cast(a0, as<i16_t>());
          auto odd  = shr(xx&maskhi, a1)&masklow;
          auto even = shr(xx, a1)&maskhi;
          return bit_cast(odd+even, as<r_t>());
         }
      }
      else if constexpr(sizeof(T) == 2) { return _mm_srli_epi16(a0, a1); }
      else if constexpr(sizeof(T) == 4) { return _mm_srli_epi32(a0, a1); }
      else if constexpr(sizeof(T) == 8) { return _mm_srli_epi64(a0, a1); }
    }
    else
    {
      if constexpr(sizeof(T) == 1) { return map(eve::shr, a0, a1); }
      if constexpr(sizeof(T) == 2) { return _mm_srai_epi16(a0, a1); }
      if constexpr(sizeof(T) == 4) { return _mm_srai_epi32(a0, a1); }
      if constexpr(sizeof(T) == 8)
      {
        return map(eve::shr, a0, a1);
      }
    }
  }

  template<integral_real_scalar_value T,  integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>  shr_(EVE_SUPPORTS(avx_),
                                         wide<T, N, sse_> const &a0,
                                         wide<I, N, sse_> const &a1) noexcept
  {
    if constexpr(supports_xop)
    {
      using si_t = wide<as_integer_t<I, signed>, N, sse_>;
      auto sa1   = -bit_cast(a1, as_<si_t>{});
      if constexpr(std::is_unsigned_v<T>)
      {
        if constexpr(sizeof(T) == 1)
          return _mm_shl_epi8(a0, sa1);
        else if constexpr(sizeof(T) == 2)
          return _mm_shl_epi16(a0, sa1);
        else if constexpr(sizeof(T) == 4)
          return _mm_shl_epi32(a0, sa1);
        else if constexpr(sizeof(T) == 8)
          return _mm_shl_epi64(a0, sa1);
      }
      else
      {
        if constexpr(sizeof(T) == 1)
          return _mm_sha_epi8(a0, sa1);
        else if constexpr(sizeof(T) == 2)
          return _mm_sha_epi16(a0, sa1);
        else if constexpr(sizeof(T) == 4)
          return _mm_sha_epi32(a0, sa1);
        else if constexpr(sizeof(T) == 8)
          return _mm_sha_epi64(a0, sa1);
      }
    }
    else
      return map(eve::shr, a0, a1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> shr_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0,I const & a1) noexcept
  {
    if constexpr(current_api >= avx2)
    {
      if constexpr(std::is_unsigned_v<T>)
      {
        if constexpr(sizeof(T) == 1)
        {
          using r_t = wide<T, N, avx_>;
          using N16 = fixed<N::value/2>;
          using i16_t = wide<std::uint16_t, N16>;
          const i16_t masklow(0xff);
          const i16_t maskhi (0xff00);
          auto xx =  bit_cast(a0, as<i16_t>());
          auto odd  = shr(xx&maskhi, a1)&masklow;
          auto even = shr(xx, a1)&maskhi;
          return bit_cast(odd+even, as<r_t>());
        }
        else if constexpr(sizeof(T) == 2)
          return _mm256_srli_epi16(a0, a1);
        else if constexpr(sizeof(T) == 4)
          return _mm256_srli_epi32(a0, a1);
        else if constexpr(sizeof(T) == 8)
          return _mm256_srli_epi64(a0, a1);
      }
      else
      {
        if constexpr(sizeof(T) == 1 || sizeof(T) == 8)
          return shr_(EVE_RETARGET(sse2_), a0, a1);
        else if constexpr(sizeof(T) == 2)
          return _mm256_srai_epi16(a0, a1);
        else if constexpr(sizeof(T) == 4)
          return _mm256_srai_epi32(a0, a1);
      }
    }
    else
      return map(shr, a0, a1);
  }

  template<integral_real_scalar_value T, integral_real_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> shr_(EVE_SUPPORTS(avx_),
       wide<T, N, avx_> const &a0,
       wide<I, N, avx_> const &a1) noexcept
  {
    [[ maybe_unused ]] auto ifxop_choice = [](const auto &a0, const auto &a1) {
      if constexpr(supports_xop)
        return shr_(EVE_RETARGET(sse2_), a0, a1);
      else
        return map(shr, a0, a1);
    };

    if constexpr(current_api >= avx2)
    {
      if constexpr(std::is_unsigned_v<T>)
      {
        if constexpr(sizeof(T) <= 2) return ifxop_choice(a0, a1);
        if constexpr(sizeof(T) == 4) return _mm256_srlv_epi32(a0, a1);
        if constexpr(sizeof(T) == 8) return _mm256_srlv_epi64(a0, a1);
      }
      else
      {
        if constexpr(sizeof(T) <= 2 || sizeof(T) == 8) return ifxop_choice(a0, a1);
        if constexpr(sizeof(T) == 4) return _mm256_srav_epi32(a0, a1);
      }
    }
    else
    {
      return ifxop_choice(a0, a1);
    }
  }
}
