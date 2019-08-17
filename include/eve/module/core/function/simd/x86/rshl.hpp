//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/function/abs.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(avx_)
                           , wide<T, N, sse_> const &a0
                           , wide<I, N, sse_> const &a1) noexcept
  requires(wide<T, N, sse_>, Integral<T>, Integral<I>)
  {
    EVE_ASSERT(assert_good_shift< wide<T, N, sse_>>(eve::abs(a1)),
               "[eve::rshl xop sse] -  At least one of " << a1 << "elements is out of the range [0, "
               << sizeof(T) * 8 << "[.");
    if constexpr(supports_xop)
    {
      if (std::is_signed_v<I>)
      {
        if constexpr(sizeof(T) == 1)       return _mm_sha_epi8(a0,a1); 
        else if constexpr(sizeof(T) == 2)  return _mm_sha_epi16(a0,a1);   
        else if constexpr(sizeof(T) == 4)  return _mm_sha_epi32(a0,a1);   
        else if constexpr(sizeof(T) == 8)  return _mm_sha_epi64(a0,a1);
      }
      else
      {
        if constexpr(sizeof(T) == 1)       return _mm_shl_epi8(a0,a1); 
        else if constexpr(sizeof(T) == 2)  return _mm_shl_epi16(a0,a1);   
        else if constexpr(sizeof(T) == 4)  return _mm_shl_epi32(a0,a1);   
        else if constexpr(sizeof(T) == 8)  return _mm_shl_epi64(a0,a1);
      }
    }
    else return map(eve::rshl, a0, a1); 
  }

}

#endif
  
