//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE4_1_EXTRACT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve ::detail
{
  template<typename T, typename N, typename I, auto v>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(sse4_1_),
                             wide<T, N, sse_> const &v0,
                             std::integral_constant<I, v> const &) noexcept
  {
    std::cout << "latte" << std::endl; 
    using i_t =  std::integral_constant<I, v>;
    enum { value = i_t::value };
    
    if constexpr(sizeof(T) == 1) {
      return T(_mm_extract_epi8(v0, value));
    }
    
    if constexpr(sizeof(T) == 2) {
      return T(_mm_extract_epi16(v0, value));
    }
    
    if constexpr(sizeof(T) == 4 && std::is_integral_v<T>)
    {
      return T(_mm_extract_epi32(v0, value));
    }
    
    if constexpr(sizeof(T) == 4 && std::is_floating_point_v<T>)
    {
      float f; 
      _MM_EXTRACT_FLOAT(f, v0, value);
      return f; 
    }
    
#if  EVE_COMP_IS_MSVC
    
    if constexpr(sizeof(T) == 8 && std::is_integral_v<T>)
    {
      return _mm_extract_epi64(v0, value);
    }
#endif      
#ifdef  EVE_ARCH_IS_X86_64
    
    if constexpr(sizeof(T) == 4 && std::is_floating_point_v<T>)
    {
      return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v0), i_t::value * 4)));
    }
    
    if constexpr(sizeof(T) == 8)
    {
      if constexpr(std::is_integral_v<T>)
      {
        return _mm_cvtsi128_si64(_mm_srli_si128(v0, value * 8));
      }
      else
      {
        return _mm_cvtsd_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(v0), value * 8)));
      }
    }
    
#endif
    
  }
  
}

#endif
