//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> mul_(EVE_SUPPORTS(avx2_),
                                        wide<T, N, avx_> const &v0,
                                        wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, double>) return _mm256_mul_pd(v0, v1);
      if constexpr(std::is_same_v<T, float>)  return _mm256_mul_ps(v0, v1);
    }
    else
    { 
      if constexpr(sizeof(T) == 1)
      {
        using i2_t = wide < std::int16_t, fixed<16>, avx_>;
        i2_t mask = Constant<i2_t,0x00FF>();
        auto const hmul = _mm256_mullo_epi16( _mm256_srli_epi16(v0.storage(), 8)
                                            , _mm256_srli_epi16(v1.storage(), 8)
                                            );
        
        return _mm256_or_si256( _mm256_and_si256(mask, _mm256_mullo_epi16(v0,v1))
                              , _mm256_slli_epi16( _mm256_and_si256(mask, hmul), 8)
                              );
      }
      else if constexpr(sizeof(T) == 2)
        return _mm256_mullo_epi16(v0, v1);
      else if constexpr(sizeof(T) == 4)
        return _mm256_mullo_epi32(v0, v1);
      else
        return map(mul, v0, v1); 
    }
    
  }
  
}

#endif
