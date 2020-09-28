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
#include <eve/function/logical_not.hpp>
#include <eve/function/is_greater.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(sse2_),
                                      wide<T, N, x86_128_> const &v0,
                                      wide<T, N, x86_128_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_128_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return l_t(_mm_cmple_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmple_pd(v0, v1));
    else if constexpr(std::is_integral_v<T>)     return logical_not(is_greater(v0, v1));
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(avx_),
                                      wide<T, N, x86_128_> const &v0,
                                      wide<T, N, x86_128_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_128_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return l_t(_mm_cmp_ps(v0, v1, _CMP_LE_OQ));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmp_pd(v0, v1, _CMP_LE_OQ));
    else  if constexpr(std::is_integral_v<T>)
    {
      if constexpr(supports_xop)
      {
#if defined(__clang__)
#  if !defined(_MM_PCOMCTRL_LE)
#    define _MM_PCOMCTRL_LE 1
#    define _MM_PCOMCTRL_LE_MISSING
#  endif
        if(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 1)      return l_t(_mm_com_epi8(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 2) return l_t(_mm_com_epi16(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 4) return l_t(_mm_com_epi32(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 8) return l_t(_mm_com_epi64(v0, v1, _MM_PCOMCTRL_LE));
        }
        else if(unsigned_value<T>)
        {
          if constexpr(sizeof(T) == 1)      return l_t(_mm_com_epu8(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 2) return l_t(_mm_com_epu16(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 4) return l_t(_mm_com_epu32(v0, v1, _MM_PCOMCTRL_LE));
          else if constexpr(sizeof(T) == 8) return l_t(_mm_com_epu64(v0, v1, _MM_PCOMCTRL_LE));
        }
#  ifdef _MM_PCOMCTRL_LE_MISSING
#    undef _MM_PCOMCTRL_LE
#    undef _MM_PCOMCTRL_LE_MISSING
#  endif
#else
        if(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 1)      return l_t(_mm_comle_epi8(v0, v1));
          else if constexpr(sizeof(T) == 2) return l_t(_mm_comle_epi16(v0, v1));
          else if constexpr(sizeof(T) == 4) return l_t(_mm_comle_epi32(v0, v1));
          else if constexpr(sizeof(T) == 8) return l_t(_mm_comle_epi64(v0, v1));
        }
        else
        {
          if constexpr(sizeof(T) == 1)      return l_t(_mm_comle_epu8(v0, v1));
          else if constexpr(sizeof(T) == 2) return l_t(_mm_comle_epu16(v0, v1));
          else if constexpr(sizeof(T) == 4) return l_t(_mm_comle_epu32(v0, v1));
          else if constexpr(sizeof(T) == 8) return l_t(_mm_comle_epu64(v0, v1));
        }
#endif
      }
      else                                  return logical_not(is_greater(v0, v1));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(avx_),
                                      wide<T, N, x86_256_> const &v0,
                                      wide<T, N, x86_256_> const &v1) noexcept
  {
    using t_t = wide<T, N, x86_256_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return l_t(_mm256_cmp_ps(v0, v1, _CMP_LE_OQ));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm256_cmp_pd(v0, v1, _CMP_LE_OQ));
    else if constexpr(std::is_integral_v<T>)     return logical_not(is_greater(v0, v1));
  }
}

