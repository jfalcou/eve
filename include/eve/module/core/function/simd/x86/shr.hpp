//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &a0, I const & a1) noexcept
  requires(wide<T, N, sse_>, integral<T>, integral<I>)
  {
    using t_t = wide<T, N, sse_>;

    if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
        using int_t     = std::uint16_t;
        using gen_t     = wide<int_t, fixed<N::value / 2>>;
        t_t const Mask1 = bit_cast(gen_t(0x00ff),as(a0));
        t_t const Mask2 = bit_cast(gen_t(0xff00),as(a0));
        t_t       tmp   = bit_and(a0, Mask1);
        t_t       tmp1  = _mm_srli_epi16(tmp, int(a1));
        tmp1            = bit_and(tmp1, Mask1);
        tmp             = bit_and(a0, Mask2);
        t_t tmp3        = _mm_srli_epi16(tmp, int(a1));
        return bit_or(tmp1, bit_and(tmp3, Mask2));
      }
      if constexpr(sizeof(T) == 2) { return _mm_srli_epi16(a0, a1); }
      if constexpr(sizeof(T) == 4) { return _mm_srli_epi32(a0, a1); }
      if constexpr(sizeof(T) == 8) { return _mm_srli_epi64(a0, a1); }
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

  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  shr_(EVE_SUPPORTS(avx_),
       wide<T, N, sse_> const &a0,
       wide<I, N, sse_> const &a1) noexcept requires(wide<T, N, sse_>, integral<T>, integral<I>)
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
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0,I const & a1) noexcept
  requires(wide<T, N, avx_>, integral<T>, integral<I>)
  {
    if constexpr(current_api >= avx2)
    {
      if constexpr(std::is_unsigned_v<T>)
      {
        if constexpr(sizeof(T) == 1)
          return shr_(EVE_RETARGET(sse2_), a0, a1);
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

  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  shr_(EVE_SUPPORTS(avx_),
       wide<T, N, avx_> const &a0,
       wide<I, N, avx_> const &a1) noexcept requires(wide<T, N, avx_>, integral<T>, integral<I>)
  {
    auto ifxop_choice = [](const auto &a0, const auto &a1) {
      if constexpr(supports_xop)
        return shr_(EVE_RETARGET(sse2_), a0, a1);
      else
        return map(shr, a0, a1);
    };

    ignore(ifxop_choice);

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

#endif
