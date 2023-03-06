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
  auto doublereal_unary_dispatch(eve::tag::cos_, D const & , Z const& a0) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}))
  {
    auto ax = eve::abs(a0);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > pio_4(as(ax)), allbits,  cos_eval(sqr(ax)));
    else
    {
      auto med = [](auto xx){
        auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
        auto sign = one(as((xx)));
        auto x = eve::abs(xx);
        auto toobig = x >  lossth;

        auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

        // strip high bits of integer part to prevent integer overflow
        auto z = ldexp( y, -4 );
        z = floor(z);           // integer part of y/8
        z = y - ldexp( z, 4 );  // y - 16 * (y/16)

        auto yj = z;
        auto test = is_odd(yj);
        y =  if_else(test, y+1, y);
        yj =  if_else(test, yj+1, yj);
        yj =  yj-trunc(yj/8)*8;
        test =  yj > Z(3);
        yj    = if_else(test, yj-4, yj);
        sign = if_else(test != (yj > one(as(yj))), -sign, sign);

        // Extended precision modular arithmetic
        z = ((x - y * dp1) - y * dp2) - y * dp3;

        auto zz = sqr(z);
        auto r = if_else( is_equal(Z(yj), Z(1)) || is_equal(Z(yj), Z(2))
                        , sin_eval(zz, z) //z  +  z * (zz * horner( zz, S))
                        , cos_eval(zz)); //oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C));
        auto res = if_else(toobig, nan(as(x)), sign*r);
        return res;
      };

      if constexpr(std::same_as<D, half_circle_type>)
      {
        return if_else(ax > pio_2(as(ax)), allbits, med(ax));
      }
      if constexpr(std::same_as<D, full_circle_type>)
      {
        return if_else(ax > pi(as(ax)), allbits, med(ax));
      }
      else if constexpr(std::same_as<D, medium_type>)
      {
        auto dd_medium_limit =  1.0e15;
        return if_else(ax > Z(dd_medium_limit), allbits, med(ax));
      }
      else
      {
        auto sign = signnz(ax);
        auto [nn, x, dx] = internal::rem_piby2(ax);
        auto n = if_else(nn > 3, nn-4, nn);
        auto alpha = if_else(is_odd(n), zero, one(as(x))); //c coef
        auto beta  = if_else(is_odd(n), one(as(x)), zero); //s coef
        sign *=  if_else((n == Z(1) || n == Z(2)), mone(as(x)), one(as(x)));
        auto x2 = x*x;
        auto s =   sign*sin_eval(x2, x);
        auto c =   sign*cos_eval(x2);
        auto res = c*alpha+s*beta;
        return res;
      }
    }
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cos_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= pio_4(as(a0))) )
      {
        return quarter_circle(cos)(a0);
      }
      else if( eve::all(x <= pio_2(as(a0))) )
      {
        auto xx = a0;
        auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
        auto sign = one(as((xx)));
        auto x = eve::abs(xx);
        auto toobig = x >  lossth;

        auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

        // strip high bits of integer part to prevent integer overflow
        auto z = ldexp( y, -4 );
        z = floor(z);           // integer part of y/8
        z = y - ldexp( z, 4 );  // y - 16 * (y/16)

        auto yj = z;
        auto test = is_odd(yj);
        y =  if_else(test, y+1, y);
        yj =  if_else(test, yj+1, yj);
        yj =  yj-trunc(yj/8)*8;
        test =  yj > Z(3);
        yj    = if_else(test, yj-4, yj);
        sign = if_else(test != (yj > one(as(yj))), -sign, sign);

        // Extended precision modular arithmetic
        z = ((x - y * dp1) - y * dp2) - y * dp3;

        auto zz = sqr(z);
        auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2)
                        , z  +  z * (zz * horner( zz, S))
                        , oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C));
        return if_else(toobig, nan(as(x)), sign*r);
        // return half_circle(cos)(a0);
      }
      else if( eve::all(x <= pi(as(x))) )
      {
        return full_circle(cos)(a0);
      }
      else if( eve::all(x <= Z(1.0e15)) )
      {
        return medium(cos)(a0);
      }
      else
      {
        return big(cos)(a0);
      }
    }
    else return apply_over(cos, a0);
  }
}
