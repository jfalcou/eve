//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // /=
  //================================================================================================
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div(wide<T, N> &self, U const &other) noexcept
      requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
    {
      return self_div(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      constexpr auto c = categorize<type>();

            if constexpr  ( c == category::float64x8  ) self = _mm512_div_pd(self, other);
      else  if constexpr  ( c == category::float64x4  ) self = _mm256_div_pd(self, other);
      else  if constexpr  ( c == category::float64x2  ) self = _mm_div_pd(self, other);
      else  if constexpr  ( c == category::float32x16 ) self = _mm512_div_ps(self, other);
      else  if constexpr  ( c == category::float32x8  ) self = _mm256_div_ps(self, other);
      else  if constexpr  ( c == category::float32x4  ) self = _mm_div_ps(self, other);
      else  if constexpr  ( c == category::int32x4 && current_api >= avx  )
      {
        auto dividend = _mm256_cvtepi32_pd(self);
        auto divisor  = _mm256_cvtepi32_pd(other);
        self = _mm256_cvttpd_epi32(_mm256_div_pd(dividend, divisor));
      }
      else
      {
        auto s = self;
        constexpr auto sdiv = [](auto a, auto b) { return a /= b; };
        if constexpr( N::value >= 2  )  self = aggregate(sdiv, s, other);
        else                            self = map(sdiv, s, other);
      }

      return self;
    }
  }
}
