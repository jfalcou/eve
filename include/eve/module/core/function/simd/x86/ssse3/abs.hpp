//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSSE3_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSSE3_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> abs_(EVE_SUPPORTS(ssse3_), wide<T, N, sse_> const &v) noexcept
  {
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(!std::is_signed_v<T>)                    return v;
      if constexpr( std::is_signed_v<T> && sizeof(T) == 1)  return _mm_abs_epi8(v);
      if constexpr( std::is_signed_v<T> && sizeof(T) == 2)  return _mm_abs_epi16(v);
      if constexpr( std::is_signed_v<T> && sizeof(T) == 4)  return _mm_abs_epi32(v);
      if constexpr( std::is_signed_v<T> && sizeof(T) == 8)  return abs_(EVE_RETARGET(simd_),v);
    }
    if constexpr(std::is_floating_point_v<T>)
    {
      return bitwise_notand(Mzero(as(v)),v);
    }
  }
}

#endif
