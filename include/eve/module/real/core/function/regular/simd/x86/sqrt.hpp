//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_SUPPORTS(sse2_), wide<T, N> a0) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

         if constexpr ( c == category::float64x8  ) return _mm512_sqrt_pd(a0);
    else if constexpr ( c == category::float32x16 ) return _mm512_sqrt_ps(a0);
    else if constexpr ( c == category::float64x4  ) return _mm256_sqrt_pd(a0);
    else if constexpr ( c == category::float32x8  ) return _mm256_sqrt_ps(a0);
    else if constexpr ( c == category::float64x2  ) return _mm_sqrt_pd   (a0);
    else if constexpr ( c == category::float32x4  ) return _mm_sqrt_ps   (a0);
  }
}
