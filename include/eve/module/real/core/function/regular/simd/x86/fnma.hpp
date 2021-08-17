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
#include <eve/function/fma.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fnma_(EVE_SUPPORTS(avx2_),
                                         wide<T, N> const &a,
                                         wide<T, N> const &b,
                                         wide<T, N> const &c) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr ( std::is_same_v<T, double> )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_>                  ) return _mm512_fnmadd_pd(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && supports_fma4 ) return _mm256_fnmadd_pd(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> && supports_fma3 ) return _mm_fnmadd_pd   (a, b, c);
      else                                                                       return fnma_           (EVE_RETARGET(cpu_), a, b, c);
    }
    else
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_>                  ) return _mm512_fnmadd_ps(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && supports_fma4 ) return _mm256_fnmadd_ps(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> && supports_fma3 ) return _mm_fnmadd_ps   (a, b, c);
      else                                                                       return fnma_           (EVE_RETARGET(cpu_), a, b, c);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> fnma_(EVE_SUPPORTS(sse2_), C const &cx, wide<T, N> const &v
                 , wide<T, N> const &w
                 , wide<T, N> const &x) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return fnma_(EVE_RETARGET(cpu_),cx,v,w,x);
    }
    else
    {
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

      if constexpr(!C::has_alternative)
      {
        if constexpr(c == category::float32x16) return _mm512_mask_fnmadd_ps   (v,m,w,x);
        else  if constexpr(c == category::float64x8 ) return _mm512_mask_fnmadd_pd   (v,m,w,x);
        else  if constexpr(c == category::float32x8)  return _mm256_mask_fnmadd_ps(v,m,w,x);
        else  if constexpr(c == category::float64x4 ) return _mm256_mask_fnmadd_pd(v,m,w,x);
        else  if constexpr(c == category::float32x4)  return _mm_mask_fnmadd_ps   (v,m,w,x);
        else  if constexpr(c == category::float64x2 ) return _mm_mask_fnmadd_pd   (v,m,w,x);
        else  return fnma_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
      else
      {
        auto src  = alternative(cx,v,as<wide<T, N>>{});
        return fnma_(EVE_RETARGET(cpu_),cx,v,w,x);
      }
    }
  }
}
