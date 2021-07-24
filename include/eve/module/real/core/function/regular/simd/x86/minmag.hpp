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

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ABI> minmag_(EVE_SUPPORTS(sse2_),
                                          wide<T, N> const &v0,
                                          wide<T, N> const &v1) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();
    constexpr auto ctrl = range_ctrl::absolute_min | range_ctrl::sign_from_cmp;
    // float
          if constexpr( cat == category::float32x4  ) return _mm_range_ps(v0, v1, ctrl);
    else  if constexpr( cat == category::float32x8  ) return _mm256_range_ps(v0, v1, ctrl);
    else  if constexpr( cat == category::float32x16 ) return _mm512_range_ps(v0, v1, ctrl);
    // double
    else  if constexpr( cat == category::float64x2  ) return _mm_range_pd(v0, v1, ctrl);
    else  if constexpr( cat == category::float64x4  ) return _mm256_range_pd(v0, v1, ctrl);
    else  if constexpr( cat == category::float64x8  ) return _mm512_range_pd(v0, v1, ctrl);
    else  return minmag_(EVE_RETARGET(cpu_), v0, v1);
  }
}
