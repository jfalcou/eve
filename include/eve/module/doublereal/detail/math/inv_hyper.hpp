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

}
