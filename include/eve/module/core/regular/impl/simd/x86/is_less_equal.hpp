//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/traits/as_logical.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // masked  implementation
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_equal_(EVE_REQUIRES(avx512_), C const& mask, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr( C::has_alternative  || O::contains(almost) )
    {
      return is_less_equal.behavior(as<logical<wide<T, N>>>{}, opts, a, b);
    }
    else
    {
      auto const            s = alternative(mask, a, as(to_logical(a)));
      [[maybe_unused]] auto m = expand_mask(mask, as(a)).storage().value;
      constexpr auto        c = categorize<wide<T, N>>();
      constexpr auto        f = to_integer(cmp_flt::le_oq);

      if      constexpr( C::is_complete )            return s;
      else if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x8 )  return mask8 {_mm512_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::float32x8 )  return mask8 {_mm256_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x4 )  return mask8 {_mm256_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::float32x4 )  return mask8 {_mm_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x2 )  return mask8 {_mm_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::int64x8 )    return mask8 {_mm512_mask_cmple_epi64_mask(m, a, b)};
      else if constexpr( c == category::int64x4 )    return mask8 {_mm256_mask_cmple_epi64_mask(m, a, b)};
      else if constexpr( c == category::int64x2 )    return mask8 {_mm_mask_cmple_epi64_mask(m, a, b)};
      else if constexpr( c == category::int32x16 )   return mask16 {_mm512_mask_cmple_epi32_mask(m, a, b)};
      else if constexpr( c == category::int32x8 )    return mask8 {_mm256_mask_cmple_epi32_mask(m, a, b)};
      else if constexpr( c == category::int32x4 )    return mask8 {_mm_mask_cmple_epi32_mask(m, a, b)};
      else if constexpr( c == category::int16x32 )   return mask32 {_mm512_mask_cmple_epi16_mask(m, a, b)};
      else if constexpr( c == category::int16x16 )   return mask16 {_mm256_mask_cmple_epi16_mask(m, a, b)};
      else if constexpr( c == category::int16x8 )    return mask8 {_mm_mask_cmple_epi16_mask(m, a, b)};
      else if constexpr( c == category::int8x64 )    return mask64 {_mm512_mask_cmple_epi8_mask(m, a, b)};
      else if constexpr( c == category::int8x32 )    return mask32 {_mm256_mask_cmple_epi8_mask(m, a, b)};
      else if constexpr( c == category::int8x16 )    return mask16 {_mm_mask_cmple_epi8_mask(m, a, b)};
      else if constexpr( c == category::uint64x8 )   return mask8 {_mm512_mask_cmple_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint64x4 )   return mask8 {_mm256_mask_cmple_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint64x2 )   return mask8 {_mm_mask_cmple_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint32x16 )  return mask16 {_mm512_mask_cmple_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint32x8 )   return mask8 {_mm256_mask_cmple_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint32x4 )   return mask8 {_mm_mask_cmple_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint16x32 )  return mask32 {_mm512_mask_cmple_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint16x16 )  return mask16 {_mm256_mask_cmple_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint16x8 )   return mask8 {_mm_mask_cmple_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint8x64 )   return mask64 {_mm512_mask_cmple_epu8_mask(m, a, b)};
      else if constexpr( c == category::uint8x32 )   return mask32 {_mm256_mask_cmple_epu8_mask(m, a, b)};
      else if constexpr( c == category::uint8x16 )   return mask16 {_mm_mask_cmple_epu8_mask(m, a, b)};
    }
  }
}
