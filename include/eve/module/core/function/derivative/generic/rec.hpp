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

#include <eve/function/converter.hpp>
#include <eve/function/derivative/rec.hpp>
#include <eve/function/derivative/pow.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mone.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T rec_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using i_t =  as_integer_t<element_type_t<N>, signed>;
      using f_t =  element_type_t<T>;
      auto sn = -to_<i_t>(n);
      auto res = to_<f_t>(factorial(n))*pow(x, sn-1);
      return if_else(is_odd(n), mone, one(as(x)))*res;
    }
    else
      return apply_over(derivative2(rec), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T rec_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x) noexcept
  {

    return -rec(sqr(x));
  }
}
