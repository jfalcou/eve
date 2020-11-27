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

#include <eve/function/log_abs.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/none.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T log_abs(EVE_SUPPORTS(cpu_)
                                     , derivative_type<1> const &
                                     , T x
                                     , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      auto tmp = inc(-2*to_<elt_t>(n-(n/2)*2))*pow_abs(rec(x), n)*factorial(dec(n));
      if (none(is_eqz(n))) return tmp;
      return if_else(is_gtz(n), tmp, log_abs(x));
    }
    else
      return apply_over(derivative1(log), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log_abs(EVE_SUPPORTS(cpu_)
                                     , derivative_type<1> const &
                                     , T x) noexcept
  {
    return rec(x);
  }
}
