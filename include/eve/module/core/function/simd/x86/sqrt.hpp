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

#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> sqrt_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
      return _mm_sqrt_ps(a0);
    else if constexpr(std::is_same_v<T, double>)
      return _mm_sqrt_pd(a0);
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> sqrt_(EVE_SUPPORTS(avx2_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
      return _mm256_sqrt_ps(a0);
    else if constexpr(std::is_same_v<T, double>)
      return _mm256_sqrt_pd(a0);
  }

}

