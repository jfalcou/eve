//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> trunc_(EVE_SUPPORTS(sse4_1_), wide<T, N> a0) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

         if constexpr ( c == category::float64x8  ) return _mm512_roundscale_pd(a0, _MM_FROUND_TO_ZERO);
    else if constexpr ( c == category::float32x16 ) return _mm512_roundscale_ps(a0, _MM_FROUND_TO_ZERO);
    else if constexpr ( c == category::float64x4  ) return _mm256_round_pd     (a0, _MM_FROUND_TO_ZERO);
    else if constexpr ( c == category::float32x8  ) return _mm256_round_ps     (a0, _MM_FROUND_TO_ZERO);
    else if constexpr ( c == category::float64x2  ) return _mm_round_pd        (a0, _MM_FROUND_TO_ZERO);
    else if constexpr ( c == category::float32x4  ) return _mm_round_ps        (a0, _MM_FROUND_TO_ZERO);
  }
}
