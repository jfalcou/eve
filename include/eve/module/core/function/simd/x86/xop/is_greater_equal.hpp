//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_XOP_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

#if !defined(_MM_PCOMCTRL_GE)
#define _MM_PCOMCTRL_GE 3
#define _MM_PCOMCTRL_GE_MISSING
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> is_greater_equal_(EVE_SUPPORTS(avx_),
                                                   wide<T, N, sse_> const &v0,
                                                   wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr(!std::is_integral_v<T>)
    {
      if constexpr(std::is_integral_v<T>)
      {
        auto issigned =  std::is_signed_v<T>; 
#if defined(__clang__)
        if constexpr(issigned && (sizeof(T) == 1))   return _mm_com_epi8 (v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(issigned && (sizeof(T) == 2))   return _mm_com_epi16(v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(issigned && (sizeof(T) == 4))   return _mm_com_epi32(v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(issigned && (sizeof(T) == 8))   return _mm_com_epi64(v0, v1, _MM_PCOMCTRL_GE);     
        if constexpr(!issigned && (sizeof(T) == 1))  return _mm_com_epu8 (v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(!issigned && (sizeof(T) == 2))  return _mm_com_epu16(v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(!issigned && (sizeof(T) == 4))  return _mm_com_epu32(v0, v1, _MM_PCOMCTRL_GE);
        if constexpr(!issigned && (sizeof(T) == 8))  return _mm_com_epu64(v0, v1, _MM_PCOMCTRL_GE);
#else
        if constexpr(issigned && (sizeof(T) == 1))   return _mm_comge_epi8( v0, v1);
        if constexpr(issigned && (sizeof(T) == 2))   return _mm_comge_epi16(v0, v1);
        if constexpr(issigned && (sizeof(T) == 4))   return _mm_comge_epi32(v0, v1);
        if constexpr(issigned && (sizeof(T) == 8))   return _mm_comge_epi64(v0, v1);     
        if constexpr(!issigned && (sizeof(T) == 1))  return _mm_comge_epu8( v0, v1);
        if constexpr(!issigned && (sizeof(T) == 2))  return _mm_comge_epu16(v0, v1);
        if constexpr(!issigned && (sizeof(T) == 4))  return _mm_comge_epu32(v0, v1);
        if constexpr(!issigned && (sizeof(T) == 8))  return _mm_comge_epu64(v0, v1);
#endif
      }
      else
      {
      if constexpr(std::is_same_v<T, float>)
        return as_logical_t<t_t>(_mm_cmp_ps(v0, v1, _CMP_GE_OQ));
      if constexpr(std::is_same_v<T, double>)
        return as_logical_t<t_t>(_mm_cmp_pd(v0, v1, _CMP_GE_OQ));
      }
  }

#ifdef _MM_PCOMCTRL_GE_MISSING
#undef _MM_PCOMCTRL_GE
#undef _MM_PCOMCTRL_GE_MISSING
#endif

}

#endif
