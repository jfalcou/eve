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

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_not_greater_equal_(EVE_REQUIRES(sse2_),
                                                                 O const          &o,
                                                                 wide<T, N> const &a,
                                                                 wide<T, N> const &b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto m = _CMP_NGE_UQ;

    if constexpr( O::contains(definitely))
    {
      return is_not_greater_equal.behavior(cpu_{}, o, a, b);
    }
    else
    {
      if constexpr( current_api >= eve::avx512 )
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
      else if constexpr( c == category::float32x8 ) return l_t(_mm256_cmp_ps(a, b, m));
      else if constexpr( c == category::float64x2 ) return l_t(_mm_cmpnge_pd(a, b));
      else if constexpr( c == category::float32x4 ) return l_t(_mm_cmpnge_ps(a, b));
      else return a < b;
    }
  }

// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE  as_logical_t<wide<T, N>> is_not_greater_equal_(EVE_REQUIRES(avx512_),
                                                                  C          const& mask,
                                                                  O          const& o,
                                                                  wide<T, N> const& v,
                                                                  wide<T, N> const& w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr( C::has_alternative || O::contains(definitely))
    {
      return is_not_greater_equal.behavior(cpu_{}, o && mask, v, w);
    }
    else
    {
      auto const            s = alternative(mask, v, as(to_logical(v)));
      [[maybe_unused]] auto m = expand_mask(mask, as(v)).storage().value;
      constexpr auto        c = categorize<wide<T, N>>();
      constexpr auto        f = to_integer(cmp_flt::nge_uq);

      if      constexpr( C::is_complete )            return s;
      else if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x8 )  return mask8 {_mm512_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x8 )  return mask8 {_mm256_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x4 )  return mask8 {_mm256_mask_cmp_pd_mask(m, v, w, f)};
      else if constexpr( c == category::float32x4 )  return mask8 {_mm_mask_cmp_ps_mask(m, v, w, f)};
      else if constexpr( c == category::float64x2 )  return mask8 {_mm_mask_cmp_pd_mask(m, v, w, f)};
      else return if_else(mask, zero, v < w); //is_less[mask](v, w); // circular include
    }
  }
}
