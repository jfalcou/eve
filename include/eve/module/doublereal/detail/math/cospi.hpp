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
#include <eve/module/doublereal/detail/trigo_base.hpp>
#include <eve/module/doublereal/detail/trigo_eval.hpp>

namespace eve::detail
{

  ////////////////////////////////////////////////////////////////////////////////////////////
  ///// cospi
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::cospi_, D const & , Z const& a0) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type, full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, double>)
  {
    auto ax = eve::abs(a0);
    auto pia2 = sqr(pi(eve::as<Z>())*ax);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > quarter(as(ax)), allbits,  cos_eval(pia2));
    else
    {
      auto med = [](auto ax){
        auto sign = one(as(ax)); //signnz(ax);
        auto [nn, x, dx] = rem2(ax);
        auto n = if_else(nn > 3, nn-4, nn);
        auto alpha = if_else(is_odd(n), zero, one(as(x))); //c coef
        auto beta  = if_else(is_odd(n), one(as(x)), zero); //s coef
        sign *=  if_else((n == Z(1) || n == Z(2)), mone(as(x)), one(as(x)));
        auto x2 = x*x;
        auto s =   sign*sin_eval(x2, x);
        auto c =   sign*cos_eval(x2);
        auto res = c*alpha+s*beta;
        return res;
      };

      if constexpr(std::same_as<D, half_circle_type>)
      {
        return if_else(ax > half(as(ax)), allbits, med(ax));
      }
      if constexpr(std::same_as<D, full_circle_type>)
      {
        return if_else(ax > one(as(ax)), allbits, med(ax));
      }
      else
      {
        return med(ax);
      }
    }
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::cospi_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type, full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, float>)
  {
    auto dbla = to_double(a);
    auto dblr = D()(cospi)(dbla);
    auto flrh = float32(dblr);
    auto flrl = float32(dblr-float64(flrh));
    return make_doublereal(flrh, flrl);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cospi_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= quarter(as(x))) )
      {
        return quarter_circle(cospi)(x);
      }
      else if( eve::all(x <= half(as(x))) )
      {
        return half_circle(cospi)(x);
      }
      else if( eve::all(x <= one(as(x))) )
      {
        return full_circle(cospi)(x);
      }
      else
      {
        return big(cospi)(x);
      }
    }
    else return apply_over(cospi, a0);
  }
}
