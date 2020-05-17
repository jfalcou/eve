//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_REC_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  rec_(EVE_SUPPORTS(sse2_), raw_type const &mode, wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The error for this approximation is no more than 1.5.e-12
      return _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>) { return _mm_rcp_ps(a0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> rec_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>) { return _mm_div_pd(One(as(a0)), a0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm_div_ps(One(as(a0)), a0);
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  rec_(EVE_SUPPORTS(sse2_), pedantic_type const &mode, wide<T, N, sse_> const &a0) noexcept
  {
    return  rec(a0);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  rec_(EVE_SUPPORTS(avx_), raw_type const &mode, wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The error for this approximation is no more than 1.5.e-12
      return _mm256_cvtps_pd(_mm_rcp_ps(_mm256_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>) { return _mm256_rcp_ps(a0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> rec_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0) noexcept
  {
    if constexpr(std::is_same_v<T, double>) { return _mm256_div_pd(One(as(a0)), a0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm256_div_ps(One(as(a0)), a0);
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  rec_(EVE_SUPPORTS(avx_), pedantic_type const &mode, wide<T, N, avx_> const &a0) noexcept
  {
    return rec(a0);
  }
}

#endif
