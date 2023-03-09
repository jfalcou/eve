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
  ///// sinpi
  ///////////////////////////////////////////////////////////////////////////////////////////
  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sinpi_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type, full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, double>)
  {
    auto ax = eve::abs(a);
    if constexpr(std::same_as<D, quarter_circle_type>||std::same_as<D, half_circle_type>)
    {
      auto pia = pi(eve::as<Z>())*a;
      auto pia2 = sqr(pia);
      if constexpr(std::same_as<D, quarter_circle_type>)
        return if_else(ax > quarter(as(ax)), allbits,  sin_eval(pia2, pia));
      else if constexpr(std::same_as<D, half_circle_type>)
        return if_else(ax > half(as(ax)), allbits,  sin_eval(pia2, pia));
    }
    else
    {
      auto med = [](auto a,  auto ax){
        auto sign = signnz(a);
        auto [nn, x, dx] = rem2(ax);
        x = if_else(is_not_finite(a), eve::allbits, x);                // nan or Inf input will return nan
        x = if_else(is_greater(a, maxflint(eve::as(x))), eve::zero, x);// all non infinite elements greater than maxflint are even flint
        auto n = if_else(nn > 3, nn-4, nn);
        auto alpha = if_else(is_odd(n), zero, one(as(x)));
        auto beta  = if_else(is_odd(n), one(as(x)), zero);
        sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
        auto x2= sqr(x);
        auto s =   sign*sin_eval(x2, x);
        auto c =   sign*cos_eval(x2);
        return s*alpha+c*beta;
      };

      if constexpr(std::same_as<D, full_circle_type>)
      {
        return if_else(ax > one(as(ax)), allbits,  med(a, ax));
      }
      else
        return med(a, ax);
    }
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sinpi_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type , full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, float>)
  {
    auto dbla = to_double(a);
    auto dblr = D()(sinpi)(dbla);
    auto flrh = float32(dblr);
    auto flrl = float32(dblr-float64(flrh));
    return make_doublereal(flrh, flrl);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sinpi_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= quarter(as(a0))) )
      {
        return quarter_circle(sinpi)(a0);
      }
      else if( eve::all(x <= half(as(a0))) )
      {
        return half_circle(sinpi)(a0);
      }
      else if( eve::all(x <= one(as(x))) )
      {
        return full_circle(sinpi)(a0);
      }
      else
      {
        return big(sinpi)(a0);
      }
    }
    else return apply_over(sinpi, a0);
  }
}
