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
#include <eve/module/core/regular/is_less.hpp>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
is_not_greater_equal_(EVE_SUPPORTS(sse2_),
                      wide<T, N> const                &a,
                      wide<T, N> const                &b) noexcept requires x86_abi<abi_t<T, N>>
{
  using l_t        = logical<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto m = _CMP_NGE_UQ;

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
  else return is_less(b, a);
}

// -----------------------------------------------------------------------------------------------
// masked  implementation
template<conditional_expr C, floating_scalar_value T, typename N>
EVE_FORCEINLINE auto
is_not_greater_equal_(EVE_SUPPORTS(avx512_),
                      C const         & cx,
                      wide<T, N> const& v,
                      wide<T, N> const& w) noexcept
    -> decltype(is_not_greater_equal(v, w)) requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return is_not_greater_equal_(EVE_RETARGET(cpu_), cx, v, w);
  }
  else
  {
    auto           m = expand_mask(cx, as<wide<T, N>> {}).storage().value;
    constexpr auto f = to_integer(cmp_flt::nge_uq);

    if constexpr( c == category::float32x16 ) return mask16 {_mm512_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x8 )
      return mask8 {_mm512_mask_cmp_pd_mask(m, v, w, f)};
    else if constexpr( c == category::float32x8 )
      return mask8 {_mm256_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x4 )
      return mask8 {_mm256_mask_cmp_pd_mask(m, v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_mask_cmp_ps_mask(m, v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_mask_cmp_pd_mask(m, v, w, f)};
    else return is_less[cx](v, w);
  }
}
}
