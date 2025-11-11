//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/detail/flags.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/apply_fp16.hpp>

namespace eve::detail
{

  template<std::uint8_t I, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> of_class_(EVE_REQUIRES(avx512_),
                                                  O const& opts,
                                                  wide<T, N> a,
                                                  fp_class<I> cls) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();

    using s_t = typename l_t::storage_type;

         if constexpr( c == category::float64x8 ) return s_t {_mm512_fpclass_pd_mask(a, I)};
    else if constexpr( c == category::float64x4 ) return s_t {_mm256_fpclass_pd_mask(a, I)};
    else if constexpr( c == category::float64x2 ) return s_t {_mm_fpclass_pd_mask(a, I)};
    else if constexpr( c == category::float32x16) return s_t {_mm512_fpclass_ps_mask(a, I)};
    else if constexpr( c == category::float32x8 ) return s_t {_mm256_fpclass_ps_mask(a, I)};
    else if constexpr( c == category::float32x4 ) return s_t {_mm_fpclass_ps_mask(a, I)};
    else if constexpr (match(c, category::float16) && !detail::supports_fp16_vector_ops)
    {
      constexpr auto using_bit_manip = (eve::poszero | eve::negzero | eve::posinf | eve::neginf).value;
      constexpr auto only_bit_manip = (I & ~using_bit_manip) == 0;
      constexpr auto prevents_upscale = (I & eve::denorm.value) != 0;

      if constexpr (only_bit_manip || prevents_upscale)
      {
        return of_class.behavior(cpu_{}, opts, a, cls);
      }
      else
      {
        return apply_fp16_as_fp32(of_class, a, cls);
      }
    }
    else if constexpr( c == category::float16x32) return s_t {_mm512_fpclass_ph_mask(a, I)};
    else if constexpr( c == category::float16x16) return s_t {_mm256_fpclass_ph_mask(a, I)};
    else if constexpr( c == category::float16x8 ) return s_t {_mm256_fpclass_ph_mask(a, I)};
  }


// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<std::uint8_t I, conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto of_class_(EVE_REQUIRES(avx512_),
                                   C const& cx,
                                   O const& o,
                                   fp_class<I> cls,
                                   wide<T, N> const& v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return of_class[o][cx].retarget(cpu_{}, cls, v);
    }
    else
    {
      auto m = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if constexpr( c == category::float32x16 )     return mask16 {_mm512_mask_fpclass_ps_mask(m, v, I)};
      else if constexpr( c == category::float64x8 ) return mask8 {_mm512_mask_fpclass_pd_mask(m, v, I)};
      else if constexpr( c == category::float32x8 ) return mask8 {_mm256_mask_fpclass_ps_mask(m, v, I)};
      else if constexpr( c == category::float64x4 ) return mask8 {_mm256_mask_fpclass_pd_mask(m, v, I)};
      else if constexpr( c == category::float32x4 ) return mask8 {_mm_mask_fpclass_ps_mask(m, v, I)};
      else if constexpr( c == category::float64x2 ) return mask8 {_mm_mask_fpclass_pd_mask(m, v, I)};
      else if constexpr (match(c, category::float16) && !detail::supports_fp16_vector_ops)
      {
        return apply_fp16_as_fp32_masked(of_class, cx, cls, v);
      }
      else if constexpr( c == category::float16x32) return mask32 {_mm512_mask_fpclass_ph_mask(m, v, I)};
      else if constexpr( c == category::float16x16) return mask16 {_mm256_mask_fpclass_ph_mask(m, v, I)};
      else if constexpr( c == category::float16x8 ) return mask8  {_mm256_mask_fpclass_ph_mask(m, v, I)};
    }
  }
}
