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
    Z x(half_circle(sin)(high(a)));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    return x;
  }

//  template<typename Z>
//   auto
//   dd_unary_dispatch(eve::tag::cos_, half_circle_type const & , Z const& a) noexcept
//   //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
//   {
//     auto aa = eve::abs(a);
//     Z x(half_circle(cos)(high(a)));
//     x += (acos(x)-aa)*sqrt(oneminus(sqr((x))));
//     x += (acos(x)-aa)*sqrt(oneminus(sqr((x))));
//     return x;
//   }

//   template<typename Z>
//   auto
//   dd_unary_dispatch(eve::tag::sincos_, half_circle_type const & , Z const& a) noexcept
//   //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
//   {
//     auto [ss, sc] = (half_circle(sincos)(high(a)));
//     auto s = Z(ss);
//     auto c = Z(sc);
//     s -= (asin(s)-a)*sqrt(oneminus(sqr(high(s))));
//     s -= (asin(s)-a)*sqrt(oneminus(sqr(high(s))));
//     auto aa = eve::abs(a);
//     c += (acos(c)-aa)*sqrt(oneminus(sqr((c))));
//     c += (acos(c)-aa)*sqrt(oneminus(sqr((c))));
//     return kumi::tuple{s, c};
//   }


}
