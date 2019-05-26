//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_RSHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_RSHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
#if defined(EVE_SUPPORTS_XOP)
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, sse_> rshr_(EVE_SUPPORTS(xop_)
                                       , wide<T, N, avx_> const &a0
                                       , wide<I, N, avx_> const &a1) noexcept
  {
    using t_t = wide<T, N, sse_>; 
    assert(assert_good_shift<t_t>(abs(a1)) && "[eve::rshr] (xop) a shift absolute value is out of range");
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = wide<detail::as_integer_t<T>, N, sse_>;
      return bitwise_cast<t_t>(rshr(bitwise_cast<i_t>(a0), a1));
    }
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) == 1)  return _mm_sha_epi8(a0,-a1); 
      if constexpr(sizeof(T) == 2)  return _mm_sha_epi16(a0,-a1);   
      if constexpr(sizeof(T) == 4)  return _mm_sha_epi32(a0,-a1);   
      if constexpr(sizeof(T) == 8)  return _mm_sha_epi64(a0,-a1);   
    }
  }
  
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, sse_> rshr_(EVE_SUPPORTS(xop_)
                                       , wide<T, N, avx_> const &a0
                                       , I a1) noexcept
  {
    using t_t = wide<T, N, sse_>; 
    assert(assert_good_shift<t_t>(abs(a1)) && "[eve::rshr] (xop)  shift absolute value is out of range");
    using i_t = wide<I, N, avx_>;
    return rshr(a0, i_t(a1)); 
  }

#endif

}

#endif
