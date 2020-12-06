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

#include <eve/function/rec.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
//   template<floating_real_value T, unsigned_value N>
//   EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
//                                    , derivative_type<2> const &
//                                    , T x, T y, N n) noexcept
//   {
//     if constexpr( has_native_abi_v<T> )
//     {
//       return hypot(x, y)*hypot(log(x), n);
//     }
//     else
//       return apply_over(derivative1(hypot), x, y, n);
//   }

//   template<floating_real_value T, unsigned_value N>
//   EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
//                                    , derivative_type<1> const &
//                                    , T x, T y, N p) noexcept
//   {
//     if constexpr( has_native_abi_v<T> )
//     {
//       using elt_t =  element_type_t<T>;
//       auto yp1 = inc(y);
//       auto fp = to_<elt_t>(p);
//       return (tgamma(yp1)/tgamma(yp1-fp))*hypot(x, y-fp); // TO DO better eval
//     }
//     else
//       return apply_over(derivative2(hypot), x, y, p);
//   }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return rec(hypot(x, y))*x;
  }

   template<floating_real_value T>
  EVE_FORCEINLINE constexpr T hypot_(EVE_SUPPORTS(cpu_)
                                   , derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return rec(hypot(x, y))*y;
  }
}
