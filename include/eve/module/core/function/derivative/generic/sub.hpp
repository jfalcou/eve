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

#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/derivative/plus.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return derivative(plus)(x, n)-derivative(plus)(y, p);
    }
    else
      return apply_over(derivative1(sub), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x, T ) noexcept
  {

    return one(as(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sub_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T x, T ) noexcept
  {

    return mone(as(x));
  }
}
