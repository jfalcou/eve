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
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/traits/as_logical.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>> is_not_less_(EVE_SUPPORTS(sse2_),
                                                   O          const & o,
                                                   wide<T, N> const & a,
                                                   wide<T, N> const & b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using l_t        = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T, N>>();
    constexpr auto m = _CMP_NLT_UQ;

    if constexpr( O::contains(definitely2))
    {
      return is_not_less.behavior(cpu_{}, o, a, b);
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
      else if constexpr( c == category::float64x2 ) return l_t(_mm_cmpnlt_pd(a, b));
      else if constexpr( c == category::float32x4 ) return l_t(_mm_cmpnlt_ps(a, b));
      else return is_greater_equal(b, a);
    }
  }

// -----------------------------------------------------------------------------------------------
// masked  implementation
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE  as_logical_t<wide<T, N>> is_not_less_(EVE_SUPPORTS(avx512_),
                                                         C const& mask,
                                                         O const& o,
                                                         wide<T, N> const& v,
                                                         wide<T, N> const& w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    auto const            s = alternative(mask, v, as(to_logical(v)));
    [[maybe_unused]] auto m = expand_mask(mask, as(v)).storage().value;
    constexpr auto        c = categorize<wide<T, N>>();
    constexpr auto        f = to_integer(cmp_flt::nlt_uq);

    if      constexpr( C::is_complete )            return s;
    else if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x8 )  return mask8 {_mm512_mask_cmp_pd_mask(m, v, w, f)};
    else if constexpr( c == category::float32x8 )  return mask8 {_mm256_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x4 )  return mask8 {_mm256_mask_cmp_pd_mask(m, v, w, f)};
    else if constexpr( c == category::float32x4 )  return mask8 {_mm_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x2 )  return mask8 {_mm_mask_cmp_pd_mask(m, v, w, f)};
    else return is_not_less.behavior(cpu_{}, o, v, w);
  }
}
