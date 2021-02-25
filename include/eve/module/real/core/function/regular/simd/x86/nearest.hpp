//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> nearest_(EVE_SUPPORTS(sse4_1_),
                                            wide<T, N, x86_128_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm_round_pd(a0, _MM_FROUND_TO_NEAREST_INT);
    else if constexpr(std::is_same_v<T, float>)
      return _mm_round_ps(a0, _MM_FROUND_TO_NEAREST_INT);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> nearest_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm256_round_pd(a0, _MM_FROUND_TO_NEAREST_INT);
    else if constexpr(std::is_same_v<T, float>)
      return _mm256_round_ps(a0, _MM_FROUND_TO_NEAREST_INT);
  }
}

