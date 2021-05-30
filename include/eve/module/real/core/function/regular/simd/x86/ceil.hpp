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
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> ceil_(EVE_SUPPORTS(sse4_1_), wide<T, N> const &a0) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr (std::same_as<T, double> )
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_pd(a0, _MM_FROUND_CEIL);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_pd     (a0, _MM_FROUND_CEIL);
      else                                                    return _mm_ceil_pd         (a0);
    }
    else
    {
           if constexpr (std::same_as<abi_t<T, N>, x86_512_>) return _mm512_roundscale_ps(a0, _MM_FROUND_CEIL);
      else if constexpr (std::same_as<abi_t<T, N>, x86_256_>) return _mm256_round_ps     (a0, _MM_FROUND_CEIL);
      else                                                    return _mm_ceil_ps         (a0);
    }
  }
}
