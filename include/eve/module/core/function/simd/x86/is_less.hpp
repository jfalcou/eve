//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/signmask.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_(EVE_SUPPORTS(sse2_)
                               , wide<T, N, sse_> const &v0
                               , wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return l_t(_mm_cmplt_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmplt_pd(v0, v1));
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1)            return l_t(_mm_cmplt_epi8(v0, v1));
        else if constexpr(sizeof(T) == 2)       return l_t(_mm_cmplt_epi16(v0, v1));
        else if constexpr(sizeof(T) == 4)       return l_t(_mm_cmplt_epi32(v0, v1));
        else if constexpr(sizeof(T) == 8)
        {
          if constexpr(current_api >= sse4_2)   return l_t(_mm_cmpgt_epi64(v1, v0));
          else                                  return map(eve::is_less, v0, v1);
        }
      }
      else if constexpr(std::is_unsigned_v<T>)  return is_greater(v1, v0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_(EVE_SUPPORTS(avx_)
                               , wide<T, N, avx_> const &v0
                               , wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return l_t(_mm256_cmp_ps(v0, v1, /*EVE_CMP_LT_OQ*/ 0x01));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, /*EVE_CMP_LT_OQ*/ 0x01));
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 1)           return l_t(_mm256_cmpgt_epi8(v1, v0));
          else if constexpr(sizeof(T) == 2)      return l_t(_mm256_cmpgt_epi16(v1, v0));
          else if constexpr(sizeof(T) == 4)      return l_t(_mm256_cmpgt_epi32(v1, v0));
          else if constexpr(sizeof(T) == 8)      return l_t(_mm256_cmpgt_epi64(v1, v0));
        }
        else                                    return is_greater(v1, v0);
      }
      else                                      return aggregate(eve::is_less, v0, v1);
    }
  }
}

