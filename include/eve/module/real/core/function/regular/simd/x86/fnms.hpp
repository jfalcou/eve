//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/fms.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fnms_(EVE_SUPPORTS(avx2_),
                                   wide<T, N> const &a,
                                   wide<T, N> const &b,
                                   wide<T, N> const &c) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_nmacc_ps(a, b, c);
      }
      else
        return fms(-a, b, c);
    }
    else
    {
      if constexpr( supports_xop )
      {
        if constexpr( std::is_integral_v<T> && sizeof(T) == 2 )
          return _mm_nmacc_epi16(a, b, c);
        else if constexpr( std::is_integral_v<T> && sizeof(T) == 4 )
          return _mm_nmacc_epi32(a, b, c);
        else
          return fms(-a, b, c);
      }
      else
        return fms(-a, b, c);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fnms_(EVE_SUPPORTS(avx2_),
                                   wide<T, N> const &a,
                                   wide<T, N> const &b,
                                   wide<T, N> const &c) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_nmacc_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_nmacc_ps(a, b, c);
      }
      else
        return fms(-a, b, c);
    }
    else
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
      return fnms_(EVE_RETARGET(cpu_),cx,v,w);
    }
    else
    {
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

      if constexpr(!C::has_alternative)
      {
        if constexpr(c == category::float32x16) return _mm512_mask_fnmsub_ps   (v,m,w,x);
        else  if constexpr(c == category::float64x8 ) return _mm512_mask_fnmsub_pd   (v,m,w,x);
        else  return if_else(cx,eve::fnms(v, w, x),v);
      }
      else
      {
        auto src  = alternative(cx,v,as<wide<T, N>>{});
        return if_else(cx,eve::fnms(v, w, x),src);
      }
    }
  }
}
