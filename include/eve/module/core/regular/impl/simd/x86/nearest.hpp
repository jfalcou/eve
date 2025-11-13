//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/module/core/regular/if_else.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> nearest_(EVE_REQUIRES(sse4_1_),
                                      O           const& ,
                                      wide<T, N> a0) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(almost))
    {
      return nearest.behavior(cpu_{}, o, a0);
    }
    else
    {
      constexpr int mode = _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC;
      constexpr auto c   = categorize<wide<T, N>>();

      if      constexpr( c == category::float64x8 )           return _mm512_roundscale_pd(a0, mode);
      else if constexpr( c == category::float32x16)           return _mm512_roundscale_ps(a0, mode);
      else if constexpr( c == category::float64x4 )           return _mm256_round_pd(a0, mode);
      else if constexpr( c == category::float32x8 )           return _mm256_round_ps(a0, mode);
      else if constexpr( c == category::float64x2 )           return _mm_round_pd(a0, mode);
      else if constexpr( c == category::float32x4 )           return _mm_round_ps(a0, mode);
      else if constexpr (match(c, category::float16))
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32(nearest, a0);
        else if constexpr (c == category::float16x8)          return _mm_roundscale_ph(a0, mode);
        else if constexpr (c == category::float16x16)         return _mm256_roundscale_ph(a0, mode);
        else if constexpr (c == category::float16x32)         return _mm512_roundscale_ph(a0, mode);
      }
      else                                                    return nearest.behavior(cpu_{}, o, a0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> nearest_(EVE_REQUIRES(avx512_),
                                      C          const &cx,
                                      O          const &,
                                      wide<T, N> const &v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(almost))
    {
      return nearest[o][cx].retarget(cpu_{}, v);
    }
    else
    {
      constexpr int mode = _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC;
      constexpr auto c   = categorize<wide<T, N>>();
      auto src           = alternative(cx, v, as<wide<T, N>> {});
      auto m             = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if      constexpr( C::is_complete)                      return src;
      else if constexpr( match(c, category::integer_) )       return if_else(cx, v, src);
      else if constexpr( c == category::float64x8 )           return _mm512_mask_roundscale_pd(src, m, v, mode);
      else if constexpr( c == category::float64x4 )           return _mm256_mask_roundscale_pd(src, m, v, mode);
      else if constexpr( c == category::float64x2 )           return _mm_mask_roundscale_pd(src, m, v, mode);
      else if constexpr( c == category::float32x16 )          return _mm512_mask_roundscale_ps(src, m, v, mode);
      else if constexpr( c == category::float32x8  )          return _mm256_mask_roundscale_ps(src, m, v, mode);
      else if constexpr( c == category::float32x4  )          return _mm_mask_roundscale_ps(src, m, v, mode);
      else if constexpr (match(c, category::float16))
      {
        if      constexpr (!detail::supports_fp16_vector_ops) return apply_fp16_as_fp32_masked(nearest, cx, v);
        else if constexpr (c == category::float16x32)         return _mm512_mask_roundscale_ph(src, m, v, mode);
        else if constexpr (c == category::float16x16)         return _mm256_mask_roundscale_ph(src, m, v, mode);
        else if constexpr (c == category::float16x8)          return _mm_mask_roundscale_ph(src, m, v, mode);
      }
      else                                                    return nearest[o][cx].retarget(cpu_{}, v);
    }
  }
}
