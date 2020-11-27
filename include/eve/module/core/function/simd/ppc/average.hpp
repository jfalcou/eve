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
#include <eve/constant/half.hpp>
#include <eve/function/fma.hpp>
#include <eve/forward.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> average_(EVE_SUPPORTS(vmx_)
                                           , wide<T, N, ppc_> const &v0
                                           , wide<T, N, ppc_> const &v1) noexcept
  {
    if constexpr(integral_value<T> && sizeof(T) < 8) return vec_avg(v0.storage(), v1.storage());
    else if constexpr(floating_value<T>)             return fma(v0,  half(eve::as(v0)), v1 *  half(eve::as(v0)));
    else                                             return map(average, v0, v1);
  }
}

