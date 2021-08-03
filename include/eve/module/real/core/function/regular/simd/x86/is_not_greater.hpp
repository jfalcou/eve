//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_not_greater_( EVE_SUPPORTS(sse2_), wide<T,N> const& a, wide<T,N> const& b) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    using l_t = logical<wide<T, N>>;
    constexpr auto c = categorize<wide<T,N>>();
    constexpr auto m = _CMP_NGT_UQ;

    if constexpr( current_api >= eve::avx512 )
    {
      using s_t = typename l_t::storage_type;

            if constexpr(c == category::float64x8  ) return s_t{_mm512_cmp_pd_mask(a, b, m) };
      else  if constexpr(c == category::float64x4  ) return s_t{_mm256_cmp_pd_mask(a, b, m) };
      else  if constexpr(c == category::float64x2  ) return s_t{_mm_cmp_pd_mask   (a, b, m) };
      else  if constexpr(c == category::float32x16 ) return s_t{_mm512_cmp_ps_mask(a, b, m) };
      else  if constexpr(c == category::float32x8  ) return s_t{_mm256_cmp_ps_mask(a, b, m) };
      else  if constexpr(c == category::float32x4  ) return s_t{_mm_cmp_ps_mask   (a, b, m) };
    }
    else  if constexpr(c == category::float64x4  ) return l_t(_mm256_cmp_pd   (a, b, m) );
    else  if constexpr(c == category::float32x8  ) return l_t(_mm256_cmp_ps   (a, b, m) );
    else  if constexpr(c == category::float64x2  ) return l_t(_mm_cmpngt_pd   (a, b) );
    else  if constexpr(c == category::float32x4  ) return l_t(_mm_cmpngt_ps   (a, b) );
    else  return is_less_equal(b, a);
  }


 // -----------------------------------------------------------------------------------------------
  // masked  implementation
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto is_not_greater_(EVE_SUPPORTS(avx512_), C const &cx, wide<T, N> const &v, wide<T, N> const &w)  noexcept -> decltype(is_greater(v, w))
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::has_alternative || C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return is_not_greater_(EVE_RETARGET(cpu_),cx,v, w);
    }
    else
    {
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;
      constexpr auto f = to_integer(cmp_flt::ngt_uq);

            if constexpr(c == category::float32x16) return mask16{_mm512_mask_cmp_ps_mask(m,v,w,f)};
      else  if constexpr(c == category::float64x8 ) return mask8 {_mm512_mask_cmp_pd_mask(m,v,w,f)};
      else  if constexpr(c == category::float32x8 ) return mask8 {_mm256_mask_cmp_ps_mask(m,v,w,f)};
      else  if constexpr(c == category::float64x4 ) return mask8 {_mm256_mask_cmp_pd_mask(m,v,w,f)};
      else  if constexpr(c == category::float32x4 ) return mask8 {_mm_mask_cmp_ps_mask(m,v,w,f)};
      else  if constexpr(c == category::float64x2 ) return mask8 {_mm_mask_cmp_pd_mask(m,v,w,f)};
      else  return is_less_equal[cx](w, v);
    }
  }

}
