//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{

#if defined(EVE_SUPPORTS_XOP)
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, sse_> shr_(EVE_SUPPORTS(avx_)
                                       , wide<T, N, sse_> const &a0
                                       , wide<I, N, sse_> const &a1) noexcept
  {
    using t_t = wide<T, N, sse_>; 
   EVE_ASSERT(assert_good_shift<t_t>(a1),
               "[eve::shr xop sse] -  At least one of " << a1 << "elements is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");
    if constexpr( std::is_arithmetic_v<T> )
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        static_assert (  !std::is_floating_point_v<T> &&
                        "[eve::shr] - No support for floating values"
                      );
      }
      if constexpr(std::is_integral_v<T>)
      {
        
        if constexpr(std::is_unsigned_v<T>)
        {
          using si_t = wide<as_integer_t<I,signed>, N, sse_>; 
          auto sa1 = -bitwise_cast<si_t>(a1); 
          if constexpr(sizeof(T) == 1)  return _mm_shl_epi8(a0,sa1); 
          if constexpr(sizeof(T) == 2)  return _mm_shl_epi16(a0,sa1);   
          if constexpr(sizeof(T) == 4)  return _mm_shl_epi32(a0,sa1);   
          if constexpr(sizeof(T) == 8)  return _mm_shl_epi64(a0,sa1);   
        }
        else
        {
          using si_t = wide<as_integer_t<I,signed>, N, sse_>; 
          auto sa1 = -bitwise_cast<si_t>(a1); 
          if constexpr(sizeof(T) == 1) return _mm_sha_epi8(a0,sa1);   
          if constexpr(sizeof(T) == 2) return _mm_sha_epi16(a0,sa1);   
          if constexpr(sizeof(T) == 4) return _mm_sha_epi32(a0,sa1);   
          if constexpr(sizeof(T) == 8) return _mm_sha_epi64(a0,sa1);   
        }
      }
    }
    else
    {
      static_assert ( std::is_arithmetic_v<T>,
                      "eve::shr - No support for logical values"
                    );
    }
  }
#endif
  
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, avx_>
                  shr_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0, I a1) noexcept
  {
    return aggregate(eve::shr,a0,a1);
  }
}

#endif
