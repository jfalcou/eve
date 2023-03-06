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

   template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::tan_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, double>)
  {
    auto ax = eve::abs(a);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > pio_4(as(ax)), allbits,  signnz(a)*tan_finalize(sqr(a), a));
    else if constexpr(std::same_as<D, half_circle_type>)
      return if_else(ax > pio_2(as(ax)), allbits,  signnz(a)*tan_finalize(sqr(a), a));
    else
    {
//      auto sign = signnz(a);
      auto [nn, x, dx] = internal::rem_piby2(ax);
      auto n = if_else(nn > 3, nn-4, nn);
      auto res =  tan_finalize(a, n, x, dx);
//       auto alpha = if_else(is_odd(n), zero, one(as(x)));
//       auto beta  = if_else(is_odd(n), one(as(x)), zero);
//       sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
//       auto x2 = sqr(x);
//       auto s =   sign*tan_eval(x2, x);
//       auto c =   sign*cos_eval(x2);
//       auto res = s*alpha+c*beta;
      if constexpr(std::same_as<D, full_circle_type>)
      {
        return if_else(eve::abs(x) > pi(as(ax)), allbits,  res);
      }
      else if constexpr(std::same_as<D, medium_type>)
      {
        auto dd_medium_limit =  1.0e15;
        return if_else(ax > Z(dd_medium_limit), allbits,  res);
      }
      else
        return res;
    }
    //is this better for quater and half? TODO bench
    //       Z x(quarter_circle(sin)(high(a)));
    //       x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    //       x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    //       return x;
  }


//   template<typename Z>
//   auto doublereal_unary_dispatch(eve::tag::tan_, Z const& xx) noexcept
//   {
//     auto [s, c] =  sincos(xx);
//     return s/c;
//   }

}
