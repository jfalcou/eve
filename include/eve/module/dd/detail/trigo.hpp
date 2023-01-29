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

namespace eve::detail
{

  template<typename Z>
  auto
  dd_unary_dispatch(eve::tag::sin_, half_circle_type const & , Z const& a) noexcept
  //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
  {
    Z x(sin(high(a)));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    return x;
  }
}
