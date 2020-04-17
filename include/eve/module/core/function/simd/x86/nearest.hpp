//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_NEAREST_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<floating_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> nearest_(EVE_SUPPORTS(sse4_1_),
                                            wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm_round_pd(a0, _MM_FROUND_TO_NEAREST_INT);
    else if constexpr(std::is_same_v<T, float>)
      return _mm_round_ps(a0, _MM_FROUND_TO_NEAREST_INT);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<floating_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> nearest_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm256_round_pd(a0, _MM_FROUND_TO_NEAREST_INT);
    else if constexpr(std::is_same_v<T, float>)
      return _mm256_round_ps(a0, _MM_FROUND_TO_NEAREST_INT);
  }
}

#endif
