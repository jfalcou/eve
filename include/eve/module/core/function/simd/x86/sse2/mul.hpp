//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_MUL_HPP_INCLUDED

#include <eve/wide.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename T, typename N>
  EVE_FORCEINLINE wide<double, N, sse_> mul_(EVE_SUPPORTS(sse2_),
                                             wide<double, N, sse_> const &v0,
                                             wide<double, N, sse_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, double>) return _mm_mul_pd(v0, v1);
      if constexpr(std::is_same_v<T, float>)  return _mm_mul_ps(v0, v1);
    }
    else
    {
      if constexpr(sizeof(T) == 1)
      {
        using i2_t = wide < std::int16_t, fixed<8>, sse_>;
        i2_t mask = Constant<i2_t,0x00FF>();
        return _mm_or_si128 ( _mm_and_si128(mask, _mm_mullo_epi16(v0, v1))
                            , _mm_slli_epi16
                              ( _mm_and_si128 ( mask
                                              , _mm_mullo_epi16
                                                ( _mm_srli_epi16(v0, 8)
                                                , _mm_srli_epi16(v1, 8)
                                                )
                                              )
                              , 8
                              )
                            );
      }
      else if constexpr(sizeof(T) == 2)
      {
        return _mm_mullo_epi16(v0, v1);
      }
      else if constexpr(sizeof(T) == 4)
      {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif // __clang__
        return _mm_or_si128(
          _mm_and_si128(
            _mm_mul_epu32(v0, v1),
            _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
          )
          , _mm_slli_si128(
            _mm_and_si128(
              _mm_mul_epu32( _mm_srli_si128(v0,4)
                           , _mm_srli_si128(v1,4)
                           )
              , _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
            )
            , 4
          )
        );
#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
      }
      else
      {
        return map(mul, v0, v1); 
      }
    }
    
  }

}

#endif
