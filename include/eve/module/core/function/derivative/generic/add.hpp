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

#include <eve/function/add.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T add_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {

      return if_else(is_eqz(n+p), add(x, y),
                     if_else(binarize(n+p <= 1u, one(as(x)))));
    }
    else
      return apply_over(derivative1(add), x, y, n, p);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T add_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<1> const &
                                    , T x, T ) noexcept
  {

    return one(as(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T add_(EVE_SUPPORTS(cpu_)
                                    , derivative_type<2> const &
                                    , T x, T ) noexcept
  {

    return one(as(x));
  }
}
