//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_X86_SSSE3_COMMON_SIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_X86_SSSE3_COMMON_SIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/shr.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto sign_(EVE_SUPPORTS(ssse3_)
                            ,wide<T, N, sse_> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto r = if_else[as(a)](is_gtz(a), one_, zero_)-if_one_else_zero[as(a)](is_ltz(a), one_, zero_);
#ifdef EVE_SIMD_NO_NANS
      return r;
#else
      return if_else(is_nan(aa), r, allbits_);
#endif
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1) return _mm_sign_epi8(One(as(a)), a);
        if constexpr(sizeof(T) == 2) return _mm_sign_epi16(One(as(a)), a);
        if constexpr(sizeof(T) == 4) return _mm_sign_epi32(One(as(a)), a);  
        if constexpr(sizeof(T) == 8) return map(sign, a); 
      else
        return if_else[as(a)](a, one_, zero_); 
    }   
  }
}

#endif
