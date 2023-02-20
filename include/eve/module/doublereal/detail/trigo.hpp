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

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sin_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}) && std::same_as<underlying_type_t<Z>, double>)
  {
      auto ax = eve::abs(a);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > pio_4(as(ax)), allbits,  eve::detail::internal::sin_eval(a));
    else if constexpr(std::same_as<D, half_circle_type>)
      return if_else(ax > pio_2(as(ax)), allbits,  eve::detail::internal::sin_eval(a));
    else
    {
      auto sign = signnz(a);
      auto [nn, x, dx] = internal::rem_piby2(ax);
      auto n = if_else(nn > 3, nn-4, nn);
      auto alpha = if_else(is_odd(n), zero, one(as(x)));
      auto beta  = if_else(is_odd(n), one(as(x)), zero);
      sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
      auto s =   sign*(eve::detail::internal::sin_eval)(x);
      auto c =   sign*(eve::detail::internal::cos_eval)(x);
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
    //is this better for quater and half? TODO bench
    //       Z x(quarter_circle(sin)(high(a)));
    //       x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    //       x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    //       return x;
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

  template<typename Z, decorator D>
  auto
  doublereal_unary_dispatch(eve::tag::cos_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}))
  {
      auto ax = eve::abs(a);
    if constexpr(std::same_as<D, quarter_circle_type>)
      return if_else(ax > pio_4(as(ax)), allbits,  eve::detail::internal::cos_eval(a));
    else
    {
      auto sign = signnz(a);
      auto [nn, x, dx] = internal::rem_piby2(ax);
      auto n = if_else(nn > 3, nn-4, nn);
      auto alpha = if_else(is_odd(n), zero, one(as(x)));
      auto beta  = if_else(is_odd(n), one(as(x)), zero);
      sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
      auto s =   sign*(eve::detail::internal::sin_eval)(x);
      auto c =   sign*(eve::detail::internal::cos_eval)(x);
      auto res = c*alpha-s*beta;
      if constexpr(std::same_as<D, half_circle_type>)
      {
        return if_else(ax > pio_2(as(ax)), allbits,  res);
      }
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
        return half_circle(cos)(a0);
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
// template<typename Z>
// auto
//   doublereal_unary_dispatch(eve::tag::cos_, Z const& xx) noexcept
//   {
//     auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
//     auto sign = one(as((xx)));
//     auto x = eve::abs(xx);
//     auto toobig = x >  lossth;

//     auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

//     // strip high bits of integer part to prevent integer overflow
//     auto z = ldexp( y, -4 );
//     z = floor(z);           // integer part of y/8
//     z = y - ldexp( z, 4 );  // y - 16 * (y/16)

//     auto yj = z;
//     auto test = is_odd(yj);
//     y =  if_else(test, y+1, y);
//     yj =  if_else(test, yj+1, yj);
//     yj =  yj-trunc(yj/8)*8;
//     test =  yj > Z(3);
//     yj    = if_else(test, yj-4, yj);
//     sign = if_else(test != (yj > one(as(yj))), -sign, sign);

//     // Extended precision modular arithmetic
//     z = ((x - y * dp1) - y * dp2) - y * dp3;

//     auto zz = sqr(z);
//     auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2)
//                     , z  +  z * (zz * horner( zz, S))
//                     , oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C));
//     return if_else(toobig, nan(as(x)), sign*r);
//   }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sincos_, Z const& xx) noexcept
  {
    auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
    auto csign = one(as((xx)));
    auto ssign = signnz(xx);
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

    csign = if_else(test != (yj > one(as(yj))), -csign, csign);
    ssign = if_else(test, -ssign, ssign);

    // Extended precision modular arithmetic
    z = ((x - y * dp1) - y * dp2) - y * dp3;

    auto zz = sqr(z);
    auto r1 =  z  +  z * (zz * horner( zz, S));
    auto r2 =  oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C);
    test = Z(yj) == Z(1) || Z(yj) == Z(2);
    auto sr = if_else( test, r2, r1);
    auto cr = if_else( test, r1, r2);
    sr = if_else(toobig, nan(as(x)), ssign*sr);
    cr = if_else(toobig, nan(as(x)), csign*cr);
    return kumi::tuple{sr, cr};
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::tan_, Z const& xx) noexcept
  {
    auto [s, c] =  sincos(xx);
    return s/c;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cot_, Z const& xx) noexcept
  {
    auto [s, c] =  sincos(xx);
    return c/s;
  }
}
