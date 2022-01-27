//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> fanm_(EVE_SUPPORTS(sse2_), C const &cx
                 , wide<T, N> const &v
                 , wide<T, N> const &w
                 , wide<T, N> const &x) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return fanm_(EVE_RETARGET(cpu_),cx,v,w,x);
    }
    else
    {
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

      if constexpr(!C::has_alternative)
      {
              if constexpr(c == category::float32x16) return _mm512_mask3_fnmadd_ps(w,x,v,m);
        else  if constexpr(c == category::float64x8 ) return _mm512_mask3_fnmadd_pd(w,x,v,m);
        else  if constexpr(c == category::float32x8 ) return _mm256_mask3_fnmadd_ps(w,x,v,m);
        else  if constexpr(c == category::float64x4 ) return _mm256_mask3_fnmadd_pd(w,x,v,m);
        else  if constexpr(c == category::float32x8 ) return _mm128_mask3_fnmadd_ps(w,x,v,m);
        else  if constexpr(c == category::float64x4 ) return _mm128_mask3_fnmadd_pd(w,x,v,m);
        else  return fanm_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
      else
      {
        auto src  = alternative(cx,v,as<wide<T, N>>{});
        return fanm_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
    }
  }
}
