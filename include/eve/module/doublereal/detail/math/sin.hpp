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
  auto doublereal_unary_dispatch(eve::tag::sin_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, double>)
  {
    auto ax = eve::abs(a);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > pio_4(as(ax)), allbits,  sin_eval(sqr(a), a));
    else if constexpr(std::same_as<D, half_circle_type>)
      return if_else(ax > pio_2(as(ax)), allbits,  sin_eval(sqr(a), a));
    else
    {
      auto sign = signnz(a);
      auto [nn, x, dx] = internal::rem_piby2(ax);
      auto n = if_else(nn > 3, nn-4, nn);
      auto alpha = if_else(is_odd(n), zero, one(as(x)));
      auto beta  = if_else(is_odd(n), one(as(x)), zero);
      sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
      auto x2 = sqr(x);
      auto s =   sign*sin_eval(x2, x);
      auto c =   sign*cos_eval(x2);
      auto res = s*alpha+c*beta;
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
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sin_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, float>)
  {
    auto dbla = to_double(a);
    auto dblr = sin(dbla);
    auto flrh = float32(dblr);
    auto flrl = float32(dblr-float64(flrh));
    return make_doublereal(flrh, flrl);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= pio_4(as(a0))) )
      {
        return quarter_circle(sin)(a0);
      }
      else if( eve::all(x <= pio_2(as(a0))) )
      {
        return half_circle(sin)(a0);
      }
      else if( eve::all(x <= pi(as(x))) )
      {
        return full_circle(sin)(a0);
      }
      else if( eve::all(x <= Z(1.0e15)) )
      {
        return medium(sin)(a0);
      }
      else
      {
        return big(sin)(a0);
      }
    }
    else return apply_over(sin, a0);
  }
}
