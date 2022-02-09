//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/fms.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fnms_(EVE_SUPPORTS(avx2_),
                                   wide<T, N> const &a,
                                   wide<T, N> const &b,
                                   wide<T, N> const &c
                                  ) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return fms(-a, b, c);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> fnms_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v
                 , wide<T, N> const &w
                 , wide<T, N> const &x) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return fnms_(EVE_RETARGET(cpu_),cx,v,w,x);
    }
    else
    {
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

      if constexpr(!C::has_alternative)
      {
              if constexpr(c == category::float32x16) return _mm512_mask_fnmsub_ps(v,m,w,x);
        else  if constexpr(c == category::float64x8 ) return _mm512_mask_fnmsub_pd(v,m,w,x);
        else  if constexpr(c == category::float32x8)  return _mm256_mask_fnmsub_ps(v,m,w,x);
        else  if constexpr(c == category::float64x4 ) return _mm256_mask_fnmsub_pd(v,m,w,x);
        else  if constexpr(c == category::float32x4)  return _mm_mask_fnmsub_ps(v,m,w,x);
        else  if constexpr(c == category::float64x2 ) return _mm_mask_fnmsub_pd(v,m,w,x);
        else  return fnms_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
      else
      {
        auto src  = alternative(cx,v,as<wide<T, N>>{});
        return  fnms_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
    }
  }
}
