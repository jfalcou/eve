//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::log_, Z const& x) noexcept
  {
    Z z(log(high(x)));
    z =   if_else(is_infinite(z), z, z+dec(x*exp(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }

  template<typename Z>
   auto
  doublereal_unary_dispatch(eve::tag::log2_, Z const& x) noexcept
  {
    Z z(log2(high(x)));
    z =   if_else(is_infinite(z), z, z+invlog_2(as(x))*dec(x*exp2(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::log1p_, Z const& x) noexcept
  {
    Z z(log1p(high(x)));
    Z z1 = z-exp(-z)*(expm1(z)-x);
    z =   if_else(is_infinite(z), z, z1);
    return if_else(x < mone(as(x)), nan(as(x)), z);
  }
}
