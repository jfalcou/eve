//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> trunc_(EVE_SUPPORTS(sse4_1_),
                                          wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)     return _mm_round_pd(a0, _MM_FROUND_TO_ZERO);
    else if constexpr(std::is_same_v<T, float>) return _mm_round_ps(a0, _MM_FROUND_TO_ZERO);
    else                                        return a0;
  }

 template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> trunc_(EVE_SUPPORTS(sse4_1_)
                                         , raw_type const &
                                         , wide<T, N, sse_> const &a0) noexcept
  {
    return trunc(a0); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> trunc_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)     return _mm256_round_pd(a0, _MM_FROUND_TO_ZERO);
    else if constexpr(std::is_same_v<T, float>) return _mm256_round_ps(a0, _MM_FROUND_TO_ZERO);
    else                                        return a0;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> trunc_(EVE_SUPPORTS(avx_)
                                         , raw_type const &
                                         , wide<T, N, avx_> const &a0) noexcept
  {
    return trunc(a0); 
  }
   
}

#endif
