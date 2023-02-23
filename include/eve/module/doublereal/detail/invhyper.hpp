//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/doublereal/regular/traits.hpp>
#include <eve/module/doublereal/detail/utilities.hpp>

namespace eve::detail
{

  template<typename T>
  auto doublereal_unary_dispatch(eve::tag::asinh_, T const& a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T x0(asinh(high(a0)));
      x0-= (sinh(x0)-a0)/cosh(x0);
      return x0 - (sinh(x0)-a0)/cosh(x0);
    }
    else { return apply_over(eve::asinh, a0); }
  }

  template<typename T>
  auto doublereal_unary_dispatch(eve::tag::acosh_, T const& a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T x0(acosh(high(a0)));
      x0-=  (cosh(x0)-a0)/sinh(x0);
      return x0 - (cosh(x0)-a0)/sinh(x0);
    }
    else { return apply_over(eve::acosh, a0); }
  }

  template<typename T>
  auto doublereal_unary_dispatch(eve::tag::atanh_, T const& a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto aa0 = abs(a0);
      T x0(atanh(high(a0)));
      if (eve::any(aa0 > 0.5))
        x0-=  (tanh(x0)-a0)*sqr(cosh(x0));
      if (eve::any(aa0 > 0.99))
        x0-=  (tanh(x0)-a0)*sqr(cosh(x0));
      return x0 - (tanh(x0)-a0)*sqr(cosh(x0));
    }
    else { return apply_over(eve::atanh, a0); }
  }

  template<typename T>
  auto doublereal_unary_dispatch(eve::tag::acoth_, T const& a0) noexcept
  {
    auto inva0 = rec(a0);
    auto r = atanh(inva0);
    return r;
//     if constexpr( has_native_abi_v<T> )
//     {
//       T x0(acoth(high(a0)));
//       x0 +=  (coth(x0)-a0)*sqr(sinh(x0));
//       return x0 + (coth(x0)-a0)*sqr(sinh(x0));
//     }
//     else { return apply_over(eve::acoth, a0); }
  }

}
