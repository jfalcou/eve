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
#include <eve/module/dd/regular/traits.hpp>


namespace eve::detail
{

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::rec_, Z const& z) noexcept
  {
    auto r = rec(high(z));
    Z x(r);
    x += r*(Z(1)-z*r);
    return x;
  }

  //================================================================================================
  //  unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    auto rhi = ceil(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  ceil(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::exponent_, Z const& z) noexcept
  {
    return exponent(high(z));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    auto rhi = floor(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  floor(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return z-trunc(z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto dd_unary_dispatch(eve::tag::modf_
                                        , Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple {z - t, t};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
  {
    auto f = floor(z);
    auto c = ceil(z);
    auto zmf = z-f;
    auto cmz = c-z;
    return if_else(zmf == cmz, if_else((f/2 == trunc(f/2)), f, c), if_else(zmf <  cmz, f, c));
    auto rhi = nearest(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  nearest(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }


  template<typename Z1>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::next_, Z1 const& z1) noexcept
  {
    auto nz1  = Z1(high(z1), next(low(z1)));
    auto pnz1 = Z1(high(nz1), prev(low(nz1)));

    return if_else(pnz1> z1, pnz1, nz1);
  }

  template<typename Z1>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::prev_, Z1 const& z1) noexcept
  {
    auto pz1 = Z1(high(z1), prev(low(z1)));
    auto nnz1=  Z1(high(pz1), next(low(pz1)));
    return if_else(nnz1 < z1, nnz1, pz1);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sign_, Z const& z) noexcept
  {
    return Z(sign(high(z)));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::signnz_, Z const& z) noexcept
  {
    return Z(signnz(high(z)));
  }


  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sqr_, Z const& a) noexcept
  {
    auto [ahi, alo] = a;
    auto[p1, p2] = two_sqr(ahi);
    p2 += 2 * ahi * alo;
    p2 += sqr(alo);
    auto [ s1, s2] = quick_two_add(p1, p2);
    return Z{s1, s2};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sqrt_, Z const& a) noexcept
  {
    Z r(sqrt(high(a)));
    r +=  (a-sqr(r))/(2*r);
    return r;
 //    auto err = low(a)/(2*high(r));
//     return add(err, r);
//    return r + (half(as(low(a)))*low(a))*rec(2*r);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return if_else(is_positive(high(z)), floor(z), ceil(z));
  }


  //================================================================================================
  //  Binary functions
  //================================================================================================

  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::add_, auto const& z1, auto const& z2) noexcept
  {
    return z1 + z2;
  }

  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::mul_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * z2;
  }

  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::sub_, auto const& z1, auto const& z2) noexcept
  {
    return z1 - z2;
  }

   EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::div_, auto const& z1, auto const& z2) noexcept
  {
    return z1 / z2;
  }

  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * sign(high(z2));
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 * signnz(high(z2));
  }


  //================================================================================================
  //  Binary functions with integral second parameter
  //================================================================================================
  template<typename Z1, integral_value N> //TODO this doesnot work see next.cpp
  EVE_FORCEINLINE auto
  dd_n_binary_dispatch(eve::tag::next_, Z1 const& z1, N const& n) noexcept
  {
    using r_t = as_wide_as_t<Z1, N>;
    auto nz1 = r_t(high(z1), next(low(z1), n));
    auto pnz1 = r_t(high(nz1), prev(low(z1)));
    Z1 e = prev(pnz1, n);
    return if_else(e > z1, pnz1, nz1);
  }


  template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
  EVE_FORCEINLINE auto
  dd_n_binary_dispatch(eve::tag::prev_, Z1 const& z1, N const& n) noexcept
  {
    using r_t = as_wide_as_t<Z1, N>;
    auto pz1 = r_t(high(z1), prev(low(z1), n));
    auto npz1 =  r_t(high(pz1), next(low(z1)));
    r_t e = next(npz1, n);
    return if_else(e < z1, npz1, pz1);
  }

  template<typename Z, integral_value N>
  EVE_FORCEINLINE auto dd_n_binary_dispatch(tag::ldexp_, Z const& z1, N n) noexcept
  {
    return as_wide_as_t<Z, N>(ldexp(high(z1), n), ldexp(low(z1), n));
  }


}
