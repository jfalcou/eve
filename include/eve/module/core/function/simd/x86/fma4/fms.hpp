//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_FMA4_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_FMA4_FMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> fms_(EVE_SUPPORTS(avx_), wide<T, N, sse_> const &a,
                                                            wide<T, N, sse_> const &b,
                                                            wide<T, N, sse_> const &c
                                                            ) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
# if defined(EVE_SUPPORTS_FMA4)
      if constexpr(std::is_same_v<T, double>) return _mm_msub_pd(a, b, c);
      if constexpr(std::is_same_v<T, float>)  return _mm_msub_ps(a, b, c);
# else
      return fms_(EVE_RETARGET(sse4_1_),a, b, c);
# endif
    }
    else
    {
# if defined(EVE_SUPPORTS_XOP)
      if      constexpr(std::is_integral_v<T> && sizeof(T) == 2)  return _mm_msub_epi16(a, b, c);
      else if constexpr(std::is_integral_v<T> && sizeof(T) == 4)  return _mm_msub_epi32(a, b, c);
      else                                            return fms_(EVE_RETARGET(sse4_1_),a, b, c);
# else
      return fms_(EVE_RETARGET(sse4_1_),a, b, c);
# endif
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> fms_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a,
                                                            wide<T, N, avx_> const &b,
                                                            wide<T, N, avx_> const &c
                                                            ) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
# if defined(EVE_SUPPORTS_FMA4)
      if constexpr(std::is_same_v<T, double>) return _mm256_msub_pd(a, b, c);
      if constexpr(std::is_same_v<T, float>)  return _mm256_msub_ps(a, b, c);
# else
      return aggregate(eve::fms, a, b, c);
# endif
    }
    else
    {
      return aggregate(eve::fms, a, b, c);
    }
  }
}

#endif
