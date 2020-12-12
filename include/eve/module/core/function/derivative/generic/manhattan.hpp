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

#include <eve/constant/half.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/derivative/sub.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, auto N>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y) noexcept
  requires(compatible_values<T, U>)
  {
    return arithmetic_call(derivative_type<N>()(manhattan), x, y);
  }

  template<floating_real_value T, floating_real_value U, floating_real_value V, auto N>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , U const &y
                                   , V const &z) noexcept
  requires(compatible_values<T, U> && compatible_values<T, V>)
  {
    return arithmetic_call(derivative_type<N>()(manhattan), x, y, z);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(manhattan(x, y));
     if constexpr(N == 1) return sign(x);
     if constexpr(N == 2) return sign(y);
    }
   else
     return apply_over(derivative_type<N>()(manhattan), x, y);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<N> const &
                                   , T const &x
                                   , T const &y
                                   , T const &z) noexcept
  {
   if constexpr( has_native_abi_v<T> )
    {
     auto k = rec(manhattan(x, y, z));
     if constexpr(N == 1) return sign(x);
     if constexpr(N == 2) return sign(y);
     if constexpr(N == 3) return sign(z);
    }
   else
     return apply_over(derivative_type<N>()(manhattan), x, y, z);
  }


  template<floating_real_value T, unsigned_value N, unsigned_value P>
  EVE_FORCEINLINE constexpr T manhattan_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T x
                                   , T y
                                   , N n
                                   , P p) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(n+p == 0, manhattan(x, y),
                     if_else(n+p == 1,
                             if_else(p == 1, sign(y), sign(x)),
                             zero
                            )
                    );

    }
    else
      return apply_over(derivative_1st(manhattan), x, y, n, p);
  }

}
