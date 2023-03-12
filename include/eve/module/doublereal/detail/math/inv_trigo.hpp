//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/doublereal/detail/trigo_base.hpp>
#include <eve/module/doublereal/detail/trigo_eval.hpp>


namespace eve::detail
{

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::asin_, Z const& a0) noexcept
  {
    Z r(asin(high(a0)));
    auto [s, c] = half_circle(sincos)(r);
    r -= (s-a0)/c;
    return r;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::acos_, Z const& a0) noexcept
  {
    Z r(acos(high(a0)));
    auto [s, c] = full_circle(sincos)(r);
    r += (c-a0)/s;
    return r;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::atan_, Z const& a0) noexcept
  {
    Z r(atan(high(a0)));
    auto t = half_circle(tan)(r);
    r -= (t-a0)/inc(sqr(t));
    t = half_circle(tan)(r);
    r -= (t-a0)/inc(sqr(t));
    return r;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::acot_, Z const& a0) noexcept
  {
    Z r(acot(high(a0)));
    auto c = full_circle(cot)(r);
    r += (c-a0)/inc(sqr(c));
    c = full_circle(cot)(r);
    r += (c-a0)/inc(sqr(c));
    return r;
  }

  template<typename Z>
  auto
  doublereal_binary_dispatch(eve::tag::atan2_, Z const& a0,  Z const & a1) noexcept
  {
    auto q = eve::abs(a0 / a1);
    auto z = atan(q);
    return if_else(is_positive(a1), z, (pi(eve::as(a0)) - z)) * signnz(a0);
  }
}
