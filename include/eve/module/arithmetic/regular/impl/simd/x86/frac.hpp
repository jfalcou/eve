//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>


namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation for xop
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> frac_(EVE_SUPPORTS(avx_), wide<T, N> const &a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(supports_xop)
    {
      if constexpr(std::is_same_v<T, float>)       return _mm_frcz_ps(a0);
      else if constexpr(std::is_same_v<T, double>) return _mm_frcz_pd(a0);
    }
    else  return frac_(EVE_RETARGET(cpu_), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation for xop
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> frac_(EVE_SUPPORTS(avx_), wide<T, N> const &a0) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(supports_xop)
    {
      if constexpr(std::is_same_v<T, float>      ) return _mm256_frcz_ps(a0);
      else if constexpr(std::is_same_v<T, double>) return _mm256_frcz_pd(a0);
    }
    else  return frac_(EVE_RETARGET(cpu_), a0);
  }

}
