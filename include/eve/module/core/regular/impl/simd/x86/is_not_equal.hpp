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
#include <eve/traits/as_logical.hpp>

#include <type_traits>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_not_equal_(EVE_REQUIRES(avx512_),
                                                         C          const &mask,
                                                         O          const &opts,
                                                         wide<T, N> const &v,
                                                         wide<T, N> const &w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || O::contains(definitely))
    {
      return is_not_equal.behavior(as<logical<wide<T, N>>>{}, cpu_{}, opts, v, w);
    }
    else
    {
      auto const            s = alternative(mask, v, as(to_logical(v)));
      [[maybe_unused]] auto m = expand_mask(mask, as(v)).storage().value;
      constexpr auto        f = to_integer(cmp_flt::neq_uq);

      if      constexpr( C::is_complete )            return s;
      else if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x8 )  return mask8 {_mm512_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x8 )  return mask8 {_mm256_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x4 )  return mask8 {_mm256_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x4 )  return mask8 {_mm_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x2 )  return mask8 {_mm_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::int64x8 )    return mask8 {_mm512_mask_cmpneq_epi64_mask(m, v, w)};
      else if constexpr( c == category::int64x4 )    return mask8 {_mm256_mask_cmpneq_epi64_mask(m, v, w)};
      else if constexpr( c == category::int64x2 )    return mask8 {_mm_mask_cmpneq_epi64_mask(m, v, w)};
      else if constexpr( c == category::int32x16 )   return mask16 {_mm512_mask_cmpneq_epi32_mask(m, v, w)};
      else if constexpr( c == category::int32x8 )    return mask8 {_mm256_mask_cmpneq_epi32_mask(m, v, w)};
      else if constexpr( c == category::int32x4 )    return mask8 {_mm_mask_cmpneq_epi32_mask(m, v, w)};
      else if constexpr( c == category::int16x32 )   return mask32 {_mm512_mask_cmpneq_epi16_mask(m, v, w)};
      else if constexpr( c == category::int16x16 )   return mask16 {_mm256_mask_cmpneq_epi16_mask(m, v, w)};
      else if constexpr( c == category::int16x8 )    return mask8 {_mm_mask_cmpneq_epi16_mask(m, v, w)};
      else if constexpr( c == category::int8x64 )    return mask64 {_mm512_mask_cmpneq_epi8_mask(m, v, w)};
      else if constexpr( c == category::int8x32 )    return mask32 {_mm256_mask_cmpneq_epi8_mask(m, v, w)};
      else if constexpr( c == category::int8x16 )    return mask16 {_mm_mask_cmpneq_epi8_mask(m, v, w)};
      else if constexpr( c == category::uint64x8 )   return mask8 {_mm512_mask_cmpneq_epu64_mask(m, v, w)};
      else if constexpr( c == category::uint64x4 )   return mask8 {_mm256_mask_cmpneq_epu64_mask(m, v, w)};
      else if constexpr( c == category::uint64x2 )   return mask8 {_mm_mask_cmpneq_epu64_mask(m, v, w)};
      else if constexpr( c == category::uint32x16 )  return mask16 {_mm512_mask_cmpneq_epu32_mask(m, v, w)};
      else if constexpr( c == category::uint32x8 )   return mask8 {_mm256_mask_cmpneq_epu32_mask(m, v, w)};
      else if constexpr( c == category::uint32x4 )   return mask8 {_mm_mask_cmpneq_epu32_mask(m, v, w)};
      else if constexpr( c == category::uint16x32 )  return mask32 {_mm512_mask_cmpneq_epu16_mask(m, v, w)};
      else if constexpr( c == category::uint16x16 )  return mask16 {_mm256_mask_cmpneq_epu16_mask(m, v, w)};
      else if constexpr( c == category::uint16x8 )   return mask8 {_mm_mask_cmpneq_epu16_mask(m, v, w)};
      else if constexpr( c == category::uint8x64 )   return mask64 {_mm512_mask_cmpneq_epu8_mask(m, v, w)};
      else if constexpr( c == category::uint8x32 )   return mask32 {_mm256_mask_cmpneq_epu8_mask(m, v, w)};
      else if constexpr( c == category::uint8x16 )   return mask16 {_mm_mask_cmpneq_epu8_mask(m, v, w)};
    }
  }
}
