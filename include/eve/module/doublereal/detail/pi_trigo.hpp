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
#include <boost/multiprecision/cpp_bin_float.hpp>
// #include <eve/../../test/tts/test.hpp>
// #include <eve/../../test/unit/module/doublereal/measures.hpp>

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
//        std::cout << "diff " << tts::uptype(((x/pi(as(x))+nn)-ax)) << std::endl;
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


  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sinpicospi_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= pio_4(as(a0))) )
      {
        return quarter_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= pio_2(as(a0))) )
      {
        return half_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= pi(as(x))) )
      {
        return full_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= Z(1.0e15)) )
      {
        return medium(sinpicospi)(a0);
      }
      else
      {
        return big(sinpicospi)(a0);
      }
    }
    else return apply_over(sinpicospi, a0);
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sinpicospi_, D const & d, Z const& a0) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}))
  {
    return kumi::tuple{d(sinpi)(a0), d(cospi)(a0)};//TODO optimize it
  }

  template<typename Z>
  auto doublereal_unary_dispatch(eve::tag::tanpi_, Z const& xx) noexcept
  {
    auto [s, c] =  sinpicospi(xx);
    return s/c;
  }

  template<typename Z>
  auto doublereal_unary_dispatch(eve::tag::cotpi_, Z const& xx) noexcept
  {
    auto [s, c] =  sinpicospi(xx);
    return c/s;
  }

    template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::tanpi_, D const & d, Z const& xx) noexcept
  {
    auto [s, c] =  d(sinpicospi)(xx);
    return s/c;
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::cotpi_, D const & d, Z const& xx) noexcept
  {
    auto [s, c] =  d(sinpicospi)(xx);
    return c/s;
  }

}
