//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_SUPPORTS(sse2_), raw_type, wide<T, N> a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The error for this approximation is no more than 1.5.e-12
      return _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>) { return _mm_rcp_ps(a0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_SUPPORTS(sse2_), wide<T, N> const a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(std::is_same_v<T, double>) { return _mm_div_pd(one(eve::as(a0)), a0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm_div_ps(one(eve::as(a0)), a0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_SUPPORTS(avx_), raw_type, wide<T, N> a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(std::is_same_v<T, double>)
    {
      // The error for this approximation is no more than 1.5.e-12
      return _mm256_cvtps_pd(_mm_rcp_ps(_mm256_cvtpd_ps(a0)));
    }
    else if constexpr(std::is_same_v<T, float>) { return _mm256_rcp_ps(a0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> rec_(EVE_SUPPORTS(avx_), wide<T, N> a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(std::is_same_v<T, double>) { return _mm256_div_pd(one(eve::as(a0)), a0); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm256_div_ps(one(eve::as(a0)), a0);
    }
  }
}
