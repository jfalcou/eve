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
  EVE_FORCEINLINE wide<T, N> nearest_(EVE_SUPPORTS(sse4_1_), wide<T, N> a0) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr(std::is_same_v<T, double>)
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_pd(a0, _MM_FROUND_TO_NEAREST_INT);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_pd     (a0, _MM_FROUND_TO_NEAREST_INT);
      else                                                    return _mm_round_pd        (a0, _MM_FROUND_TO_NEAREST_INT);
    }
    else
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_ps(a0, _MM_FROUND_TO_NEAREST_INT);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_ps     (a0, _MM_FROUND_TO_NEAREST_INT);
      else                                                    return _mm_round_ps        (a0, _MM_FROUND_TO_NEAREST_INT);
    }
  }
}
