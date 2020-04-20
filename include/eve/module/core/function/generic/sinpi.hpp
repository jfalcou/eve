//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SINPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SINPI_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/generic/trig_finalize.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                       , restricted_type const &
                                       , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return eve::restricted_(sin)(x*Pi<T>());
    }
    else return apply_over(restricted_(sinpi), x);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<typename D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                       , D  const &
                                       , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>) if (is_not_finite(a0)) return Nan<T>();
      auto x =  eve::abs(a0);
      if constexpr(scalar_value<T>)
      {
        if (x > Maxflint<T>()) return T(0);
      }
      else
      {
        x = if_else (is_not_finite(x), eve::allbits_, x); //Nan or Inf input
        x = if_else (is_greater(x, Maxflint(as(x))), eve::zero_, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return sin_finalize(bitofsign(a0), fn, xr, dxr);
    }
    else return apply_over(D()(sinpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                       , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto x =  abs(a0);
      if (all(eve::abs(x) <= T(0.25))) return restricted_(sinpi)(a0);
      else                             return big_(sinpi)(a0);
    }
    else                     return apply_over(sinpi, a0);
  }

}

#endif
