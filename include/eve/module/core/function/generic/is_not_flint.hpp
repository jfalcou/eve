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
#include <eve/constant/maxflint.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_not_flint_(EVE_SUPPORTS(cpu_)
                                          , T const &a) noexcept
  {
    if constexpr(integral_value<T>)        return False<T>();
    else if constexpr(has_native_abi_v<T>) return is_nez(frac(a));
    else                                   return apply_over(is_not_flint, a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_not_flint_(EVE_SUPPORTS(cpu_)
                                          , pedantic_type const &
                                          , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return False<T>();
      if constexpr(floating_value<T>) return is_nez(frac(a)) || (a > eve::Maxflint<T>());
    }
    else                              return apply_over(pedantic_(is_not_flint), a);
  }
}
