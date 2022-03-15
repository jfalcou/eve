//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/detail/implementation.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/true.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), wide<T, N> a0, int s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return to_nearest(roundscale)(a0, s);
  }

  template<int S,floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), wide<T, N> a0, std::integral_constant<int, S> s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return to_nearest(roundscale)(a0, s);
  }

  // -----------------------------------------------------------------------------------------------
  // Rouding case
  template<decorator D, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), D const &, wide<T, N> a0, int s) noexcept
  requires(   is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {})
          &&  x86_abi<abi_t<T, N>>
          )
  {
    return D()(roundscale[true_(as(a0))])(a0, s);
  }

  template<int S,decorator D, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), D const &, wide<T, N> a0, std::integral_constant<int, S> s) noexcept
  requires(   is_one_of<D>(types<toward_zero_type, downward_type, to_nearest_type, upward_type> {})
          &&  x86_abi<abi_t<T, N>>
          )
  {
    return D()(roundscale[true_(as(a0))])(a0, s);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<int S, conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), C const &cx, wide<T, N> const &a0, std::integral_constant<int, S> s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return to_nearest(roundscale[cx])(a0, s);
  }

  template < int R, typename WT> struct  rm_imm_choice
  {
    rm_imm_choice(){}

    template < typename F> EVE_FORCEINLINE auto operator()(WT src, auto m, WT a, int s, F f) const noexcept
    {
      switch ((s)){
      case 0  : return f(src, m, a, std::integral_constant<int, (0  << 4) + R>()); break;
      case 1  : return f(src, m, a, std::integral_constant<int, (1  << 4) + R>()); break;
      case 2  : return f(src, m, a, std::integral_constant<int, (2  << 4) + R>()); break;
      case 3  : return f(src, m, a, std::integral_constant<int, (3  << 4) + R>()); break;
      case 4  : return f(src, m, a, std::integral_constant<int, (4  << 4) + R>()); break;
      case 5  : return f(src, m, a, std::integral_constant<int, (5  << 4) + R>()); break;
      case 6  : return f(src, m, a, std::integral_constant<int, (6  << 4) + R>()); break;
      case 7  : return f(src, m, a, std::integral_constant<int, (7  << 4) + R>()); break;
      case 8  : return f(src, m, a, std::integral_constant<int, (8  << 4) + R>()); break;
      case 9  : return f(src, m, a, std::integral_constant<int, (9  << 4) + R>()); break;
      case 10 : return f(src, m, a, std::integral_constant<int, (10 << 4) + R>()); break;
      case 11 : return f(src, m, a, std::integral_constant<int, (11 << 4) + R>()); break;
      case 12 : return f(src, m, a, std::integral_constant<int, (12 << 4) + R>()); break;
      case 13 : return f(src, m, a, std::integral_constant<int, (13 << 4) + R>()); break;
      case 14 : return f(src, m, a, std::integral_constant<int, (14 << 4) + R>()); break;
      case 15 : return f(src, m, a, std::integral_constant<int, (15 << 4) + R>()); break;
      default : return f(src, m, a, std::integral_constant<int, (15 << 4) + R>());
      }
    }
  };

  template<conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), C const &cx, wide<T, N> const &a0, int s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    return to_nearest(roundscale[cx])(a0, s);
  }

  template<decorator D, conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), C const &cx, D const &, wide<T, N> const &a0
                        , int s) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return roundscale_(EVE_RETARGET(cpu_),cx,a0);
    }
    else
    {
      auto src  = alternative(cx,a0,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;
      using r_t = wide<T, N>;
      rm_imm_choice<D::base_type::value, r_t> ic;

            if constexpr(c == category::float32x16 )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm512_mask_roundscale_ps(src, m, a, decltype(b)::value); });
      else  if constexpr(c == category::float64x8  )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm512_mask_roundscale_pd(src, m, a, decltype(b)::value); });
      else  if constexpr(c == category::float32x8  )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm256_mask_roundscale_ps(src, m, a, decltype(b)::value); });
      else  if constexpr(c == category::float64x4  )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm256_mask_roundscale_pd(src, m, a, decltype(b)::value); });
      else  if constexpr(c == category::float32x4  )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm_mask_roundscale_ps(src, m, a, decltype(b)::value); });
      else  if constexpr(c == category::float64x2  )  return ic(src, m, a0, s, [](auto src, auto m, auto a, auto b){return _mm_mask_roundscale_pd(src, m, a, decltype(b)::value); });
    }
  }

  template<int S, decorator D, conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> roundscale_(EVE_SUPPORTS(avx512_), C const &cx, D const &, wide<T, N> const &a0
                        , std::integral_constant<int, S> ) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return roundscale_(EVE_RETARGET(cpu_),cx,a0);
    }
    else
    {
      auto src  = alternative(cx,a0,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;
      constexpr int s = ((S) << 4) +  D::base_type::value;

            if constexpr(c == category::float32x16 )  return _mm512_mask_roundscale_ps(src,m, a0, s);
      else  if constexpr(c == category::float64x8  )  return _mm512_mask_roundscale_pd(src,m, a0, s);
      else  if constexpr(c == category::float32x8  )  return _mm256_mask_roundscale_ps(src,m, a0, s);
      else  if constexpr(c == category::float64x4  )  return _mm256_mask_roundscale_pd(src,m, a0, s);
      else  if constexpr(c == category::float32x4  )  return _mm_mask_roundscale_ps(src,m, a0, s);
      else  if constexpr(c == category::float64x2  )  return _mm_mask_roundscale_pd(src,m, a0, s);

    }
  }
}
