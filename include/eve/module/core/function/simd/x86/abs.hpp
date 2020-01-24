//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> abs_(EVE_SUPPORTS(ssse3_), wide<T, N, sse_> const &v) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
      return v;
    else if constexpr(std::is_floating_point_v<T>)
      return bit_notand(Mzero(as(v)), v);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) == 1)
        return _mm_abs_epi8(v);
      else if constexpr(sizeof(T) == 2)
        return _mm_abs_epi16(v);
      else if constexpr(sizeof(T) == 4)
        return _mm_abs_epi32(v);
      else if constexpr(std::is_signed_v<T> && sizeof(T) == 8)
        return abs_(EVE_RETARGET(cpu_), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> abs_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
      return v;
    else if constexpr(std::is_floating_point_v<T>)
      return bit_notand(Mzero(as(v)), v);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)
          return _mm256_abs_epi8(v);
        else if constexpr(sizeof(T) == 2)
          return _mm256_abs_epi16(v);
        else if constexpr(sizeof(T) == 4)
          return _mm256_abs_epi32(v);
        else if constexpr(sizeof(T) == 8)
          return aggregate(eve::abs, v);
      }
      else
      {
        return aggregate(eve::abs, v);
      }
    }
  }
}

#endif
