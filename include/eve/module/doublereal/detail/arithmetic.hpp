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
#include <eve/module/doublereal/regular/traits.hpp>
#include <eve/module/doublereal/detail/utilities.hpp>


namespace eve::detail
{

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::rec_, Z const& z) noexcept
  {
    auto r = rec(high(z));
    Z x(r);
    x += r*oneminus(z*r);
    x = if_else(is_infinite(z), zero(as(z))*signnz(z), x);
    x = if_else(is_eqz(z),      inf(as(z))*signnz(z), x);
    return x;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::frexp_, Z const& z) noexcept
  {
    auto [h, n] = frexp(high(z));
    auto l = ldexp(low(z), -n);
    return kumi::tuple{Z(h, l), n};
  }

  //================================================================================================
  //  unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    auto rhi = ceil(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  ceil(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::exponent_, Z const& z) noexcept
  {
    return exponent(high(z));
  }


  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    auto rhi = floor(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  floor(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return z-trunc(z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto doublereal_unary_dispatch(eve::tag::modf_
                                        , Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple {z - t, t};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
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
  doublereal_unary_dispatch(eve::tag::next_, Z1 const& z1) noexcept
  {
    auto nz1  = make_doublereal(high(z1), next(low(z1)));
    auto pnz1 = make_doublereal(high(nz1), prev(low(nz1)));

    return if_else(pnz1> z1, pnz1, nz1);
  }

  template<typename Z1>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::prev_, Z1 const& z1) noexcept
  {
    auto pz1 = make_doublereal(high(z1), prev(low(z1)));
    auto nnz1= make_doublereal(high(pz1), next(low(pz1)));
    return if_else(nnz1 < z1, nnz1, pz1);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::sign_, Z const& z) noexcept
  {
    return Z(sign(high(z)));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::signnz_, Z const& z) noexcept
  {
    return Z(signnz(high(z)));
  }


  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::sqr_, Z const& a) noexcept
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
  doublereal_unary_dispatch(eve::tag::sqrt_, Z const& a) noexcept
  {
    Z r(sqrt(high(a)));
    r +=  (a-sqr(r))/(2*r);
    return r;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return if_else(is_positive(high(z)), floor(z), ceil(z));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::mantissa_, Z const& z) noexcept
  {
    return ldexp(z, -exponent(high(z)));
  }

  //================================================================================================
  //  Binary functions
  //================================================================================================

  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::add_, auto const& z1, auto const& z2) noexcept
  {
    return z1 + z2;
  }

  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::mul_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * z2;
  }

  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::sub_, auto const& z1, auto const& z2) noexcept
  {
    return z1 - z2;
  }

   EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::div_, auto const& z1, auto const& z2) noexcept
  {
    return z1 / z2;
  }

  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * sign(high(z2));
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 * signnz(high(z2));
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::copysign_, Z1 const& z1, Z2 const& z2) noexcept
  {
    auto [z1h, z1l] = z1;
    auto cz1h = copysign(z1h, high(z2));
    auto cz1l = if_else(cz1h != z1h, -z1l, z1l);
    return make_doublereal(cz1h, cz1l);
  }

  //================================================================================================
  //  Binary functions with integral second parameter
  //================================================================================================
  template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
  EVE_FORCEINLINE auto
  doublereal_n_binary_dispatch(eve::tag::prev_, Z1 const& z1, N const& n) noexcept;

  template<typename Z1, integral_value N> //TODO this doesnot work see next.cpp
  EVE_FORCEINLINE auto
  doublereal_n_binary_dispatch(eve::tag::next_, Z1 const& z1, N const& n) noexcept
  {
    using r_t = as_wide_as_t<Z1, N>;
    auto nz1 = r_t(high(z1), next(low(z1), n));
    auto pnz1 = r_t(high(nz1), prev(low(z1), n));
    auto e =pnz1; //prev(pnz1, n);
    return if_else(e > z1, pnz1, nz1);
  }

  template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
  EVE_FORCEINLINE auto
  doublereal_n_binary_dispatch(eve::tag::next_, Z1 const& z1, N const& n) noexcept;

  template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
  EVE_FORCEINLINE auto
  doublereal_n_binary_dispatch(eve::tag::prev_, Z1 const& z1, N const& n) noexcept
  {
    using r_t = as_wide_as_t<Z1, N>;
    auto pz1 = r_t(high(z1), prev(low(z1), n));
    auto npz1 =  r_t(high(pz1), next(low(z1)));
    auto e = next(npz1, n);
    return if_else(e < z1, npz1, pz1);
  }

  template<typename Z, integral_value N>
  EVE_FORCEINLINE auto doublereal_n_binary_dispatch(tag::ldexp_, Z const& z1, N n) noexcept
  {
    auto [zh, zl] = z1;
    auto h = ldexp(zh, n);
    auto l = ldexp(zl, n);
    return make_doublereal(h, l);
  }

  template<typename Z, typename Z1>
  EVE_FORCEINLINE auto doublereal_nary_dispatch(tag::ldexp_, Z const& z1, Z1 n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "some n are not flint");
    return as_wide_as_t<Z, Z1>(ldexp(high(z1), high(n)), ldexp(low(z1), high(n)));
  }

  template<typename Z, typename Z1, decorator D>
  EVE_FORCEINLINE auto doublereal_nary_dispatch(tag::ldexp_, D const & d, Z const& z1, Z1 n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "some n are not flint");
    return as_wide_as_t<Z, Z1>(d(ldexp)(high(z1), high(n)), d(ldexp)(low(z1), high(n)));
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto doublereal_nary_dispatch(tag::ulpdist_, Z1 const& a0, Z2 const & a1) noexcept
  {
      auto [ m1, e1] = frexp(a0);
      auto [ m2, e2] = frexp(a1);
      auto expo = -max(e1, e2);
      auto e = eve::abs(if_else( e1 == e2
                               , m1-m2
                               , ldexp(a0, expo)-ldexp(a1, expo)
                               )
                       );
      return if_else ( (is_nan(a0) && is_nan(a1)) || (a0 == a1)
                     , zero
                     , e/eve::eps(eve::as(a0))
                     );
  }


  //================================================================================================
  //  ternary functions
  //================================================================================================
  template<decorator D, typename Z1, typename Z2, typename Z3>
  EVE_FORCEINLINE auto
  doublereal_nary_dispatch(eve::tag::fma_, D const &, Z1 a, Z2  b, Z3 c) noexcept
  -> decltype(a*b+c)
  {
    using r_t = decltype(a*b+c);
    auto p = qd_mul(r_t(a), r_t(b));
    auto [q0, q1, q2, q3] = qd_add(p, r_t(c));
    auto [a0, a1] = two_add(q0, q1 + q2 + q3);
    return r_t(a0, a1);
  }
}
#include <eve/module/doublereal/detail/arithmetic_converters.hpp>
