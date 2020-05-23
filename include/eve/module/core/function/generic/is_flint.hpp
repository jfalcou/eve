//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_FLINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_FLINT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_flint_(EVE_SUPPORTS(cpu_)
                                          , T const &a) noexcept
  {
    if constexpr(integral_value<T>)        return True<T>();
    else if constexpr(has_native_abi_v<T>) return is_eqz(frac(a));
    else                                   return apply_over(is_flint, a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_flint_(EVE_SUPPORTS(cpu_)
                                          , pedantic_type const &
                                          , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return True<T>();
      if constexpr(floating_value<T>) return is_eqz(frac(a)) && (a <= eve::Maxflint<T>());
    }
    else                              return apply_over(pedantic_(is_flint), a);
  }
}

#endif
