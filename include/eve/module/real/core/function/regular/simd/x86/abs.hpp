//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
    else  if constexpr( cat && category::float_   ) return bit_notand(mzero(eve::as(v)), v);
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

// -----------------------------------------------------------------------------------------------
  // 512 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_512_> abs_(EVE_SUPPORTS(avx512_), wide<T, N, x86_512_> const &v) noexcept
  {
    constexpr auto c = categorize<wide<T, N, x86_512_>>();

         if constexpr ( c && category::unsigned_  ) return v;
         if constexpr ( c == category::float64x8  ) return _mm512_abs_pd(v);
    else if constexpr ( c == category::float32x16 ) return _mm512_abs_ps(v);
    else if constexpr ( c == category::int64x8    ) return _mm512_abs_epi64(v);
    else if constexpr ( c == category::int32x16   ) return _mm512_abs_epi32(v);
    else if constexpr ( c == category::int16x32   ) return _mm512_abs_epi16(v);
    else if constexpr ( c == category::int8x64    ) return _mm512_abs_epi8(v);
  }
}
