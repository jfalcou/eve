//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Generic function for rsqrt on X86
  template<typename Pack>
  EVE_FORCEINLINE Pack rsqrt_x86(Pack const &x) noexcept
  {
    using v_t = typename Pack::value_type;
    using i_t = as_integer_t<Pack>;
    i_t nn;
    Pack a00; 
    std::tie(a00, nn) =  pedantic_(ifrexp)(x);
    auto tst = is_odd(nn);
//    nn  = if_else(tst, nn-One(as(nn)), nn);
    nn  = dec[tst](nn); 
    a00 = mul[tst](a00,2); 
    // Local constants
    auto c8  = Pack(v_t{0.125});
    auto c3  = Pack(v_t{3});
    auto c10 = Pack(v_t{10});
    auto c15 = Pack(v_t{15});
    auto a0 = raw_(rsqrt)(a00);
    auto y  = sqr(a0) * a00;

    // Perform one Halley cubically convergent iteration
    a0 = c8 * a0 * fnma(y, fnma(c3, y, c10), c15);

    if constexpr(std::is_same_v<v_t, double>)
    {
      // To obtain extra accuracy, we need one additional Newton step
      a0 = fma(fnma(a00, sqr(a0), One(as(a0))), a0 * Half(as(a0)), a0);
    }

    if constexpr(platform::supports_infinites)
    { a0 = if_else(x == Inf(as(x)), eve::zero_, a0); }

    return if_else(is_eqz(x), Inf(as(x)), pedantic_(ldexp)(a0, -nn/2));
  }

  //------------------------------------------------------------------------------------------------
  // Regular 128 bits rsqrt
  template<typename T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) { return rsqrt_x86(a0); }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  //------------------------------------------------------------------------------------------------
  // Regular 256 bits rsqrt
  template<typename T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) { return rsqrt_x86(a0); }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  //------------------------------------------------------------------------------------------------
  // 128 bits raw rsqrt
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  rsqrt_(EVE_SUPPORTS(sse2_), raw_type const &, wide<T, N, sse_> const &a0) noexcept
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
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  //------------------------------------------------------------------------------------------------
  // 256 bits raw rsqrt
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  rsqrt_(EVE_SUPPORTS(avx_), raw_type const &, wide<T, N, avx_> const &a0) noexcept
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
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }
}

#endif
