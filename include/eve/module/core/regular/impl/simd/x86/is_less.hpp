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
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(definitely))
    {
      return is_less.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      constexpr auto f = to_integer(cmp_flt::lt_oq);

      if constexpr (current_api >= avx512)
      {
        if      constexpr (c == category::float32x16) return mask16 {_mm512_cmp_ps_mask(a, b, f)};
        else if constexpr (c == category::float32x8)  return mask8 {_mm256_cmp_ps_mask(a, b, f)};
        else if constexpr (c == category::float32x4)  return mask8 {_mm_cmp_ps_mask(a, b, f)};
        else if constexpr (c == category::float64x8)  return mask8 {_mm512_cmp_pd_mask(a, b, f)};
        else if constexpr (c == category::float64x4)  return mask8 {_mm256_cmp_pd_mask(a, b, f)};
        else if constexpr (c == category::float64x2)  return mask8 {_mm_cmp_pd_mask(a, b, f)};
        else if constexpr (c == category::uint64x8)   return mask8 {_mm512_cmplt_epu64_mask(a, b)};
        else if constexpr (c == category::uint64x4)   return mask8 {_mm256_cmplt_epu64_mask(a, b)};
        else if constexpr (c == category::uint64x2)   return mask8 {_mm_cmplt_epu64_mask(a, b)};
        else if constexpr (c == category::uint32x16)  return mask16 {_mm512_cmplt_epu32_mask(a, b)};
        else if constexpr (c == category::uint32x8)   return mask8 {_mm256_cmplt_epu32_mask(a, b)};
        else if constexpr (c == category::uint32x4)   return mask8 {_mm_cmplt_epu32_mask(a, b)};
        else if constexpr (c == category::uint16x32)  return mask32 {_mm512_cmplt_epu16_mask(a, b)};
        else if constexpr (c == category::uint16x16)  return mask16 {_mm256_cmplt_epu16_mask(a, b)};
        else if constexpr (c == category::uint16x8)   return mask8 {_mm_cmplt_epu16_mask(a, b)};
        else if constexpr (c == category::uint8x64)   return mask64 {_mm512_cmplt_epu8_mask(a, b)};
        else if constexpr (c == category::uint8x32)   return mask32 {_mm256_cmplt_epu8_mask(a, b)};
        else if constexpr (c == category::uint8x16)   return mask16 {_mm_cmplt_epu8_mask(a, b)};
        else if constexpr (c == category::int64x8)    return mask8 {_mm512_cmplt_epi64_mask(a, b)};
        else if constexpr (c == category::int64x4)    return mask8 {_mm256_cmplt_epi64_mask(a, b)};
        else if constexpr (c == category::int64x2)    return mask8 {_mm_cmplt_epi64_mask(a, b)};
        else if constexpr (c == category::int32x16)   return mask16 {_mm512_cmplt_epi32_mask(a, b)};
        else if constexpr (c == category::int32x8)    return mask8 {_mm256_cmplt_epi32_mask(a, b)};
        else if constexpr (c == category::int32x4)    return mask8 {_mm_cmplt_epi32_mask(a, b)};
        else if constexpr (c == category::int16x32)   return mask32 {_mm512_cmplt_epi16_mask(a, b)};
        else if constexpr (c == category::int16x16)   return mask16 {_mm256_cmplt_epi16_mask(a, b)};
        else if constexpr (c == category::int16x8)    return mask8 {_mm_cmplt_epi16_mask(a, b)};
        else if constexpr (c == category::int8x64)    return mask64 {_mm512_cmplt_epi8_mask(a, b)};
        else if constexpr (c == category::int8x32)    return mask32 {_mm256_cmplt_epi8_mask(a, b)};
        else if constexpr (c == category::int8x16)    return mask16 {_mm_cmplt_epi8_mask(a, b)};
      }
      else
      {
        if      constexpr (c == category::float32x8) return _mm256_cmp_ps(a, b, f);
        else if constexpr (c == category::float64x4) return _mm256_cmp_pd(a, b, f);
        else if constexpr (c == category::float32x4) return _mm_cmplt_ps(a, b);
        else if constexpr (c == category::float64x2) return _mm_cmplt_pd(a, b);
        else
        {
          constexpr auto use_avx2   = current_api >= avx2;
          constexpr auto use_sse4_1 = current_api >= sse4_1;
          constexpr auto use_sse4_2 = current_api >= sse4_2;
          constexpr auto lt         = []<typename E>(E ev, E fv) { return as_logical_t<E>(ev < fv); };

          [[maybe_unused]] auto unsigned_cmp = [](auto lhs, auto rhs)
          {
            using l_t     = logical<wide<T, N>>;
            auto const sm = signmask(as<as_integer_t<wide<T, N>, signed>>{});
            return bit_cast((bit_cast(lhs, as(sm)) - sm) < (bit_cast(rhs, as(sm)) - sm), as<l_t>{});
          };

          if      constexpr (use_avx2 && c == category::int64x4)   return _mm256_cmpgt_epi64(b, a);
          else if constexpr (use_avx2 && c == category::uint64x4)  return unsigned_cmp(a, b);
          else if constexpr (use_avx2 && c == category::int32x8)   return _mm256_cmpgt_epi32(b, a);
          else if constexpr (use_avx2 && c == category::uint32x8)  return eve::min(a, b) != b;
          else if constexpr (use_avx2 && c == category::int16x16)  return _mm256_cmpgt_epi16(b, a);
          else if constexpr (use_avx2 && c == category::uint16x16) return eve::min(a, b) != b;
          else if constexpr (use_avx2 && c == category::int8x32)   return _mm256_cmpgt_epi8(b, a);
          else if constexpr (use_avx2 && c == category::uint8x32)  return eve::min(a, b) != b;
          else if constexpr (use_sse4_2 && c == category::int64x2) return _mm_cmpgt_epi64(b, a);
          else if constexpr (c == category::int32x4)               return _mm_cmplt_epi32(a, b);
          else if constexpr (c == category::int16x8)               return _mm_cmplt_epi16(a, b);
          else if constexpr (c == category::int8x16)               return _mm_cmplt_epi8(a, b);
          else if constexpr (c == category::uint32x4)
          {
            if constexpr (use_sse4_1) return eve::min(a, b) != b;
            else                      return unsigned_cmp(a, b);
          }
          else if constexpr (c == category::uint16x8)
          {
            if constexpr (use_sse4_1) return eve::min(a, b) != b;
            else                      return unsigned_cmp(a, b);
          }
          else if constexpr (c == category::uint8x16)
          {
            if constexpr (use_sse4_1) return eve::min(a, b) != b;
            else                      return unsigned_cmp(a, b);
          }
          else return map(lt, a, b);
        }
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // masked  implementation
  template<callable_options O, conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> is_less_(EVE_REQUIRES(avx512_), C const &mask, O const &opts, wide<T, N> a, wide<T, N> b) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr( C::has_alternative || O::contains(definitely))
    {
      return is_less.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      auto const            s = alternative(mask, a, as(to_logical(a)));
      [[maybe_unused]] auto m = expand_mask(mask, as(a)).storage().value;
      constexpr auto        c = categorize<wide<T, N>>();
      constexpr auto        f = to_integer(cmp_flt::lt_oq);

      if      constexpr( C::is_complete )            return s;
      else if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x8 )  return mask8 {_mm512_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::float32x8 )  return mask8 {_mm256_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x4 )  return mask8 {_mm256_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::float32x4 )  return mask8 {_mm_mask_cmp_ps_mask(m, a, b, f)};
      else if constexpr( c == category::float64x2 )  return mask8 {_mm_mask_cmp_pd_mask(m, a, b, f)};
      else if constexpr( c == category::int64x8 )    return mask8 {_mm512_mask_cmplt_epi64_mask(m, a, b)};
      else if constexpr( c == category::int64x4 )    return mask8 {_mm256_mask_cmplt_epi64_mask(m, a, b)};
      else if constexpr( c == category::int64x2 )    return mask8 {_mm_mask_cmplt_epi64_mask(m, a, b)};
      else if constexpr( c == category::int32x16 )   return mask16 {_mm512_mask_cmplt_epi32_mask(m, a, b)};
      else if constexpr( c == category::int32x8 )    return mask8 {_mm256_mask_cmplt_epi32_mask(m, a, b)};
      else if constexpr( c == category::int32x4 )    return mask8 {_mm_mask_cmplt_epi32_mask(m, a, b)};
      else if constexpr( c == category::int16x32 )   return mask32 {_mm512_mask_cmplt_epi16_mask(m, a, b)};
      else if constexpr( c == category::int16x16 )   return mask16 {_mm256_mask_cmplt_epi16_mask(m, a, b)};
      else if constexpr( c == category::int16x8 )    return mask8 {_mm_mask_cmplt_epi16_mask(m, a, b)};
      else if constexpr( c == category::int8x64 )    return mask64 {_mm512_mask_cmplt_epi8_mask(m, a, b)};
      else if constexpr( c == category::int8x32 )    return mask32 {_mm256_mask_cmplt_epi8_mask(m, a, b)};
      else if constexpr( c == category::int8x16 )    return mask16 {_mm_mask_cmplt_epi8_mask(m, a, b)};
      else if constexpr( c == category::uint64x8 )   return mask8 {_mm512_mask_cmplt_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint64x4 )   return mask8 {_mm256_mask_cmplt_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint64x2 )   return mask8 {_mm_mask_cmplt_epu64_mask(m, a, b)};
      else if constexpr( c == category::uint32x16 )  return mask16 {_mm512_mask_cmplt_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint32x8 )   return mask8 {_mm256_mask_cmplt_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint32x4 )   return mask8 {_mm_mask_cmplt_epu32_mask(m, a, b)};
      else if constexpr( c == category::uint16x32 )  return mask32 {_mm512_mask_cmplt_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint16x16 )  return mask16 {_mm256_mask_cmplt_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint16x8 )   return mask8 {_mm_mask_cmplt_epu16_mask(m, a, b)};
      else if constexpr( c == category::uint8x64 )   return mask64 {_mm512_mask_cmplt_epu8_mask(m, a, b)};
      else if constexpr( c == category::uint8x32 )   return mask32 {_mm256_mask_cmplt_epu8_mask(m, a, b)};
      else if constexpr( c == category::uint8x16 )   return mask16 {_mm_mask_cmplt_epu8_mask(m, a, b)};
    }
  }
}
