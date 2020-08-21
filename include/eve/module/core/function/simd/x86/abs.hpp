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

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_notand.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> abs_(EVE_SUPPORTS(ssse3_), wide<T, N, ABI> const &v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

          if constexpr( cat && category::unsigned_) return v;
    else  if constexpr( cat && category::float_   ) return bit_notand(Mzero(as(v)), v);
    else  if constexpr( cat && category::size64_  ) return map(eve::abs, v);
    else  if constexpr( cat == category::int32x4  ) return _mm_abs_epi32(v);
    else  if constexpr( cat == category::int16x8  ) return _mm_abs_epi16(v);
    else  if constexpr( cat == category::int8x16  ) return _mm_abs_epi8(v);
    else  if constexpr(current_api >= avx2)
    {
          if constexpr( cat == category::int32x8  ) return _mm256_abs_epi32(v);
    else  if constexpr( cat == category::int16x16 ) return _mm256_abs_epi16(v);
    else  if constexpr( cat == category::int8x32  ) return _mm256_abs_epi8(v);
    }
    else                                            return aggregate(eve::abs, v);
  }
}
