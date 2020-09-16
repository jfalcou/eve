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

#include <eve/detail/implementation.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T sqr_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    return a * a;
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto sqr_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return sqr(a0);
      }
      else if constexpr(scalar_value<T>)
      {
        return (eve::saturated_(eve::abs)(a0) > sqrtvalmax(eve::as(a0))) ? valmax(eve::as(a0)) : sqr(a0);
      }
      else
      {
        return if_else((saturated_(abs)(a0) > sqrtvalmax(eve::as(a0))), valmax(eve::as(a0)), sqr(a0));
      }
    }
    else
    {
      return apply_over(saturated_(sqr), a0);
    }
  }
}
