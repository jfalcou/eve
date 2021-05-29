//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation only
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N>
  mul_(EVE_SUPPORTS(avx_), saturated_type const &, wide<T, N> v0, wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(supports_xop)
    {
           if constexpr(std::is_same_v<T, std::int32_t>) return  _mm_maccs_epi32(v0,v1,zero(eve::as(v0)));
      else if constexpr(std::is_same_v<T, std::int16_t>) return  _mm_maccs_epi16(v0,v1,zero(eve::as(v0)));
      else return mul_(EVE_RETARGET(cpu_), saturated_type(), v0, v1);
    }
    else return mul_(EVE_RETARGET(cpu_), saturated_type(), v0, v1);
  }
}
