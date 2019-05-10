//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_FNMA4_FNMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_FNMA4_FNMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/unary_minus.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> fnma_(EVE_SUPPORTS(avx_), wide<T, N, sse_> const &a,
                                                            wide<T, N, sse_> const &b,
                                                            wide<T, N, sse_> const &c
                                                            ) noexcept
  {
    using t_t = wide<T, N, sse_>; 
    if constexpr(std::is_floating_point_v<T>)
    {
# if defined(EVE_SUPPORTS_FNMA4)
      if constexpr(std::is_same_v<T, double>) return -t_t(_mm_msub_pd(a, b, c));
      if constexpr(std::is_same_v<T, float>)  return -t_t(_mm_msub_ps(a, b, c));
# else
      return fnma_(EVE_RETARGET(sse4_1_),a, b, c);
# endif
    }
    else
    {
# if defined(EVE_SUPPORTS_XOP)
      if      constexpr(std::is_integral_v<T> && sizeof(T) == 2)  return -t_t(_mm_msub_epi16(a, b, c));
      else if constexpr(std::is_integral_v<T> && sizeof(T) == 4)  return -t_t(_mm_msub_epi32(a, b, c));
      else                                            return fnma_(EVE_RETARGET(sse4_1_),a, b, c);
# else
      return fnma_(EVE_RETARGET(sse4_1_),a, b, c);
# endif
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> fnma_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a,
                                                            wide<T, N, avx_> const &b,
                                                            wide<T, N, avx_> const &c
                                                            ) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
# if defined(EVE_SUPPORTS_FNMA4)
      if constexpr(std::is_same_v<T, double>) return -t_t(_mm256_msub_pd(a, b, c));
      if constexpr(std::is_same_v<T, float>)  return -t_t(_mm256_msub_ps(a, b, c));
# else
      return aggregate(eve::fnma, a, b, c);
# endif
    }
    else
    {
      return aggregate(eve::fnma, a, b, c);
    }
  }
}

#endif
