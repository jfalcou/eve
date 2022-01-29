//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/sqr.hpp>
#include <eve/module/arithmetic/regular/is_eqz.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Generic function for rsqrt on X86
  template<typename Pack>
  EVE_FORCEINLINE Pack rsqrt_x86(Pack const &x) noexcept
  {
    using v_t = typename Pack::value_type;
    // Local constants
    auto c8  = Pack(v_t{0.125});
    auto c3  = Pack(v_t{3});
    auto c10 = Pack(v_t{10});
    auto c15 = Pack(v_t{15});
    auto a0 = raw(rsqrt)(x);
    auto y  = sqr(a0) * x;

    // Perform one Halley cubically convergent iteration
    a0 = c8 * a0 * fnma(y, fnma(c3, y, c10), c15);

    if constexpr(std::is_same_v<v_t, double>)
    {
      // To obtain extra accuracy, we need one additional Newton step
      a0 = fma(fnma(x, sqr(a0), one(eve::as(a0))), a0 * half(eve::as(a0)), a0);
    }

    if constexpr(platform::supports_infinites)
    { a0 = if_else(x == inf(eve::as(x)), eve::zero, a0); }

    return if_else(is_eqz(x), inf(eve::as(x)), a0);
  }

  template<typename Pack>
  EVE_FORCEINLINE Pack rsqrt_x86_pedantic(Pack const &x) noexcept
  {
    using v_t =  typename Pack::value_type;
    if(eve::any(is_denormal(x)) || (std::is_same_v<v_t, double> && eve::any(eve::abs(x) < smallestposval(eve::as<float>()) || eve::abs(x) > valmax(eve::as<float>()))))
      // this is necessary because of the poor initialisation by float intrinsic
    {
      auto [a00, nn] =  pedantic(ifrexp)(x);
      auto tst = is_odd(nn);
      nn  = dec[tst](nn);
      a00 = mul[tst](a00,2);
      auto a0 = rsqrt_x86(a00);
      return if_else(is_eqz(x), inf(eve::as(x)), pedantic(ldexp)(a0, -nn/2));
    }
    else
    {
      return rsqrt_x86(x);
    }
  }

  //------------------------------------------------------------------------------------------------
  // Regular 128 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_), wide<T, N> const &a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(std::is_same_v<T, double>) return rsqrt_x86_pedantic(a0);
    else return rsqrt_x86(a0);
  }

  //------------------------------------------------------------------------------------------------
  // Regular 256 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(avx_), wide<T, N> const &a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(std::is_same_v<T, double>) return rsqrt_x86_pedantic(a0);
    else return rsqrt_x86(a0);
  }


//------------------------------------------------------------------------------------------------
  // 128 bits raw rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_SUPPORTS(sse2_), raw_type, wide<T, N> a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The maximum error for this approximation is 1.5e-12
      return _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm_rsqrt_ps(a0);
    }
  }

  //------------------------------------------------------------------------------------------------
  // 256 bits raw rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_SUPPORTS(avx_), raw_type, wide<T, N> a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The maximum error for this approximation is 1.5e-12
      return _mm256_cvtps_pd(_mm_rsqrt_ps(_mm256_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm256_rsqrt_ps(a0);
    }
  }

  //------------------------------------------------------------------------------------------------
  // avx512 bits raw rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rsqrt_(EVE_SUPPORTS(avx512_), raw_type, wide<T, N> a0) noexcept
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr(c == category::float32x16) return _mm512_rsqrt_ps   (a0);
    else  if constexpr(c == category::float64x8 ) return _mm512_rsqrt14_pd (a0);
    else  if constexpr(c == category::float32x8 ) return _mm256_rsqrt_ps   (a0);
    else  if constexpr(c == category::float64x4 ) return _mm256_rsqrt14_pd (a0);
    else  if constexpr(c == category::float32x4 ) return _mm_rsqrt_ps      (a0);
    else  if constexpr(c == category::float64x2 ) return _mm_rsqrt14_pd    (a0);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE
  wide<T, N> rsqrt_(EVE_SUPPORTS(avx512_), C const &cx, raw_type const &, wide<T, N> const &v) noexcept
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
    {
      return rsqrt_(EVE_RETARGET(cpu_),cx,v);
    }
    else
    {
      auto src  = alternative(cx,v,as<wide<T, N>>{});
      auto m    = expand_mask(cx,as<wide<T, N>>{}).storage().value;

            if constexpr(c == category::float32x16) return _mm512_mask_rsqrt_ps   (src,m,v);
      else  if constexpr(c == category::float64x8 ) return _mm512_mask_rsqrt14_pd (src,m,v);
      else  if constexpr(c == category::float32x16) return _mm256_mask_rsqrt_ps   (src,m,v);
      else  if constexpr(c == category::float64x8 ) return _mm256_mask_rsqrt14_pd (src,m,v);
      else  if constexpr(c == category::float32x16) return _mm_mask_rsqrt_ps      (src,m,v);
      else  if constexpr(c == category::float64x8 ) return _mm_mask_rsqrt14_pd    (src,m,v);
   }
  }

}
