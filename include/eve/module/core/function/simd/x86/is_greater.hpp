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

#include <eve/traits/as_logical.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/sub.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <type_traits>
namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(sse2_)
                                  , wide<T, N, sse_> const &v0
                                  , wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

         if constexpr(std::is_same_v<T, float>)  return l_t(_mm_cmpgt_ps(v0, v1));
    else if constexpr(std::is_same_v<T, double>) return l_t(_mm_cmpgt_pd(v0, v1));
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1)      return l_t(_mm_cmpgt_epi8(v0, v1));
        else if constexpr(sizeof(T) == 2) return l_t(_mm_cmpgt_epi16(v0, v1));
        else if constexpr(sizeof(T) == 4) return l_t(_mm_cmpgt_epi32(v0, v1));
        else if constexpr(sizeof(T) == 8)
        {
          if constexpr(current_api >= sse4_2) return l_t(_mm_cmpgt_epi64(v0, v1));
          else                                return map(eve::is_greater, v0, v1);
        }
      }
      else if constexpr(std::is_unsigned_v<T>)
      {
        using s_t    = eve::wide<eve::detail::as_integer_t<T, signed>, N, sse_>;
        s_t const sm = Signmask<s_t>();

        return eve::bit_cast( eve::is_greater ( eve::bit_cast(v0,as(sm)) - sm,
                                                eve::bit_cast(v1,as(sm)) - sm
                                              ),
                              as_<l_t>{}
                            );
      }
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(avx_),
                                   wide<T, N, sse_> const &v0,
                                   wide<T, N, sse_> const &v1) noexcept
  {
    using t_t = wide<T, N, sse_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(supports_xop)
    {
#if defined(__clang__)
#  if !defined(_MM_PCOMCTRL_GT)
#    define _MM_PCOMCTRL_GT 2
#    define _MM_PCOMCTRL_GT_MISSING
#  endif
      if(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1)      return l_t(_mm_com_epi8(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 2) return l_t(_mm_com_epi16(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 4) return l_t(_mm_com_epi32(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 8) return l_t(_mm_com_epi64(v0, v1, _MM_PCOMCTRL_GT));
      }
      else
      {
        if constexpr(sizeof(T) == 1)      return l_t(_mm_com_epu8(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 2) return l_t(_mm_com_epu16(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 4) return l_t(_mm_com_epu32(v0, v1, _MM_PCOMCTRL_GT));
        else if constexpr(sizeof(T) == 8) return l_t(_mm_com_epu64(v0, v1, _MM_PCOMCTRL_GT));
      }
#  ifdef _MM_PCOMCTRL_GT_MISSING
#    undef _MM_PCOMCTRL_GT
#    undef _MM_PCOMCTRL_GT_MISSING
#  endif
#else
      if(std::is_signed_v<T>)
      {
        if constexpr(sizeof(T) == 1)      return l_t(_mm_comgt_epi8(v0, v1));
        else if constexpr(sizeof(T) == 2) return l_t(_mm_comgt_epi16(v0, v1));
        else if constexpr(sizeof(T) == 4) return l_t(_mm_comgt_epi32(v0, v1));
        else if constexpr(sizeof(T) == 8) return l_t(_mm_comgt_epi64(v0, v1));
      }
      else
      {
        if constexpr(sizeof(T) == 1)      return l_t(_mm_comgt_epu8(v0, v1));
        else if constexpr(sizeof(T) == 2) return l_t(_mm_comgt_epu16(v0, v1));
        else if constexpr(sizeof(T) == 4) return l_t(_mm_comgt_epu32(v0, v1));
        else if constexpr(sizeof(T) == 8) return l_t(_mm_comgt_epu64(v0, v1));
      }
#endif
    }
    else                                  return is_greater_(EVE_RETARGET(sse2_), v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_greater_(EVE_SUPPORTS(avx_)
                                  , wide<T, N, avx_> const &v0
                                  , wide<T, N, avx_> const &v1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    using l_t = as_logical_t<t_t>;

    if constexpr(std::is_same_v<T, float>)       return as_logical_t<t_t>(_mm256_cmp_ps(v0, v1, _CMP_GT_OQ));
    else if constexpr(std::is_same_v<T, double>) return as_logical_t<t_t>(_mm256_cmp_pd(v0, v1, _CMP_GT_OQ));
    else if  constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 1)      return l_t(_mm256_cmpgt_epi8(v0, v1));
          else if constexpr(sizeof(T) == 2) return l_t(_mm256_cmpgt_epi16(v0, v1));
          else if constexpr(sizeof(T) == 4) return l_t(_mm256_cmpgt_epi32(v0, v1));
          else if constexpr(sizeof(T) == 8) return l_t(_mm256_cmpgt_epi64(v0, v1));
        }
        else
        {
          using s_t    = eve::wide<eve::detail::as_integer_t<T, signed>, N, avx_>;
          s_t const sm = Signmask<s_t>();

          return eve::bit_cast( eve::is_greater ( eve::bit_cast(v0,as(sm)) - sm,
                                                  eve::bit_cast(v1,as(sm)) - sm
                                                ),
                                as_<l_t>{}
                              );
        }
      }
      else
      {
        return aggregate(eve::is_greater, v0, v1);
      }
    }
  }
}
