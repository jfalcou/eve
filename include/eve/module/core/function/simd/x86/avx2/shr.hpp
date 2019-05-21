//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(avx2_)
                           , wide<T, N, avx_> const &a0
                           , I a1) noexcept
  requires(wide<T, N, avx_>, Integral<T>, Integral<I>)
  {
    EVE_ASSERT( (detail::assert_good_shift<wide<T, N, avx_>>(a1)),
               "[eve::shr avx2] -  At least one of " << a1 << "elements is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");

    if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) == 1)  return map(eve::shr, a0, a1); //shr_(EVE_RETARGET(sse2_),a0, a1);
      if constexpr(sizeof(T) == 2)  return _mm256_srli_epi16(a0, a1);
      if constexpr(sizeof(T) == 4)  return _mm256_srli_epi32(a0, a1);
      if constexpr(sizeof(T) == 8)  return _mm256_srli_epi64(a0, a1);
    }
    else
    {
      if constexpr(sizeof(T) == 1 || sizeof(T) == 8) return map(eve::shr, a0, a1); //shr_(EVE_RETARGET(sse2_),a0, a1);
      if constexpr(sizeof(T) == 2)                   return _mm256_srai_epi16(a0, a1);
      if constexpr(sizeof(T) == 4)                   return _mm256_srai_epi32(a0, a1);
    }
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(avx2_)
                           , wide<T, N, avx_> const &a0
                           , wide<I, N, avx_> const &a1) noexcept
  requires(wide<T, N, avx_>, Integral<T>, Integral<I>)
  {
    EVE_ASSERT((detail::assert_good_shift<wide<T, N, avx_>>(a1)),
               "[eve::shr avx2] -  At least one of " << a1 << "elements is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");
    if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) <= 2)  return map(eve::shr, a0, a1); //shr_(EVE_RETARGET(sse2_),a0, a1);
      if constexpr(sizeof(T) == 4)  return _mm256_srlv_epi32(a0, a1);
      if constexpr(sizeof(T) == 8)  return _mm256_srlv_epi64(a0, a1);
    }
    else
    {
      if constexpr(sizeof(T) <= 2 || sizeof(T) == 8) return map(eve::shr, a0, a1); //shr_(EVE_RETARGET(sse2_),a0, a1);
      if constexpr(sizeof(T) == 4)                   return _mm256_srav_epi32(a0, a1);
    }
  }

}

#endif
