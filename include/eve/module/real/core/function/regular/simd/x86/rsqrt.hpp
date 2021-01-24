//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/mul.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

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
    else return rsqrt_x86(x);
  }

  //------------------------------------------------------------------------------------------------
  // Regular 128 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_), wide<T, N, x86_128_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>) return rsqrt_x86_pedantic(a0);
    else return rsqrt_x86(a0);
  }

  //------------------------------------------------------------------------------------------------
  // Regular 256 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(avx_), wide<T, N, x86_256_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>) return rsqrt_x86_pedantic(a0);
    else return rsqrt_x86(a0);
  }


//------------------------------------------------------------------------------------------------
  // 128 bits raw rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_>
                  rsqrt_(EVE_SUPPORTS(sse2_), raw_type const &, wide<T, N, x86_128_> const &a0) noexcept
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
  EVE_FORCEINLINE wide<T, N, x86_256_>
                  rsqrt_(EVE_SUPPORTS(avx_), raw_type const &, wide<T, N, x86_256_> const &a0) noexcept
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
}
