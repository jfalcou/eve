//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto  is_equal_(EVE_SUPPORTS(sse2_)
                                 , wide<T, N, sse_> const &v0
                                 , wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

         if constexpr(std::is_same_v<T, float>)      return l_t(_mm_cmpeq_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>)     return l_t(_mm_cmpeq_pd(v0, v1));
    else if constexpr(integral_value<T>)
    {
      if constexpr(sizeof(T) == 1)                   return l_t(_mm_cmpeq_epi8(v0, v1));
      else if constexpr(sizeof(T) == 2)              return l_t(_mm_cmpeq_epi16(v0, v1));
      else if constexpr(sizeof(T) == 4)              return l_t(_mm_cmpeq_epi32(v0, v1));
      else if constexpr(sizeof(T) == 8)
      {
        if constexpr(current_api >= sse4_1)          return l_t(_mm_cmpeq_epi64(v0, v1));
        else                                         return map(is_equal, v0, v1);
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_equal_(EVE_SUPPORTS(avx_)
                                , wide<T, N, avx_> const &v0
                                , wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    using l_t = as_logical_t<t_t>;

         if constexpr(std::is_same_v<T, float>)    return l_t(_mm256_cmp_ps(v0, v1, _CMP_EQ_OQ));
    else if constexpr(std::is_same_v<T, double>)   return l_t(_mm256_cmp_pd(v0, v1, _CMP_EQ_OQ));
    else if constexpr(integral_value<T>)
    {
      if constexpr(  current_api >= avx2)
      {
             if constexpr(sizeof(T) == 1)          return l_t(_mm256_cmpeq_epi8(v0, v1));
        else if constexpr(sizeof(T) == 2)          return l_t(_mm256_cmpeq_epi16(v0, v1));
        else if constexpr(sizeof(T) == 4)          return l_t(_mm256_cmpeq_epi32(v0, v1));
        else if constexpr(sizeof(T) == 8)          return l_t(_mm256_cmpeq_epi64(v0, v1));
      }
      else                                         return aggregate(is_equal, v0, v1); //is_equal_(EVE_RETARGET(sse2_), v0, v1);
    }
  }
}

#endif
