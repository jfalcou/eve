//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_ordered_(EVE_REQUIRES(sse2_),
                                                  O          const &,
                                                  wide<T, N> const &a,
                                                  wide<T, N> const &b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto m = _CMP_ORD_Q;

    if constexpr( match(c, category::integer_) ) return true_(eve::as<l_t>());
    else if constexpr( current_api >= eve::avx512 )
    {
      using s_t = typename l_t::storage_type;

      if constexpr( c == category::float64x8 ) return s_t {_mm512_cmp_pd_mask(a, b, m)};
      else if constexpr( c == category::float64x4 ) return s_t {_mm256_cmp_pd_mask(a, b, m)};
      else if constexpr( c == category::float64x2 ) return s_t {_mm_cmp_pd_mask(a, b, m)};
      else if constexpr( c == category::float32x16 ) return s_t {_mm512_cmp_ps_mask(a, b, m)};
      else if constexpr( c == category::float32x8 ) return s_t {_mm256_cmp_ps_mask(a, b, m)};
      else if constexpr( c == category::float32x4 ) return s_t {_mm_cmp_ps_mask(a, b, m)};
    }
    else if constexpr( c == category::float64x4 ) return l_t(_mm256_cmp_pd(a, b, m));
    else if constexpr( c == category::float64x2 ) return l_t(_mm_cmpord_pd(a, b));
    else if constexpr( c == category::float32x8 ) return l_t(_mm256_cmp_ps(a, b, m));
    else if constexpr( c == category::float32x4 ) return l_t(_mm_cmpord_ps(a, b));
  }

// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto is_ordered_(EVE_REQUIRES(avx512_),
                                   C          const& cx,
                                   O          const& o,
                                   wide<T, N> const& v,
                                   wide<T, N> const& w) noexcept
  -> decltype(is_ordered(v, w))
    requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return is_ordered.behavior(cpu_{}, o, v, w);
    }
    else
    {
      auto           m = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      constexpr auto f = to_integer(cmp_flt::ord_q);

      if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x8 )
        return mask8 {_mm512_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x8 )
        return mask8 {_mm256_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x4 )
        return mask8 {_mm256_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x4 ) return mask8 {_mm_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x2 ) return mask8 {_mm_mask_cmp_pd_mask(m, v, w, f)};
    }
  }
}
