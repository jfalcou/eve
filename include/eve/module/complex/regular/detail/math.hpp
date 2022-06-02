//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex/regular/traits.hpp>
#include <eve/module/complex/regular/conj.hpp>
#include <eve/module/complex/regular/i.hpp>
#include <eve/module/complex/regular/exp_i.hpp>
#include <eve/module/complex/regular/exp_ipi.hpp>

namespace eve::detail
{

  //==============================================================================================
  // sqrt cosh cos acosh asinh atan exp exp_i exp_ipi log rec
  // acos asin atanh are in specific files
  //==============================================================================================

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : sqrt
  //===-------------------------------------------------------------------------------------------
  template<decorator D, typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::sqrt_
                                              , D const &
                                              , Z const& z
                                              ) noexcept
  {
    //always compute the sqrt of the complex with positive imaginary part
    //then conjugate if necessary
    auto [rz, iz] = z;
    auto negimag = is_ltz(iz);
    auto x = abs(rz);
    auto y = abs(iz);
    auto iaz = if_else(negimag, -iz, iz); // always >= 0 or -Nan
    auto gtxy = (x > y);
    auto gezrz = is_gez(rz);
    auto r = if_else(gtxy, y/x, x/y);
    auto rr= sqrt(inc(sqr(r)));
    auto sqrtx = sqrt(x);
    auto w = if_else(gtxy,
                     sqrtx*sqrt(half(as(r))*inc(rr)),
                     sqrt(y)*sqrt(half(as(r))*(r+rr)));
    auto is_real_z = is_real(z);
    auto res = Z(if_else(is_real_z, sqrtx, w)
                , if_else(is_real_z, zero, iaz*half(as(r))/w));
    res = if_else(gezrz, res, Z(imag(res), real(res)));
    if constexpr(std::same_as<D, pedantic_type>)
    {
      auto infty = inf(as(iaz));
      res = if_else(iaz == infty,  Z{infty, infty}, z);
      res = if_else(logical_andnot(rz == -infty, is_nan(iz)), Z{if_else(iaz == infty, iaz, zero), infty}, res);
      res = if_else(is_eqz(iz) && is_nan(rz), z, res);
      res = if_else(is_nan(z), Z(nan(as(iz)), nan(as(iz))), res);
      res = if_else(is_eqz(iz) && is_gez(rz), Z(rz), res);
    }
    return if_else(negimag, conj(res), res);
 }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::sqrt_, Z const& z) noexcept
  {
    return regular(sqrt)(z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== cosh
  //===-------------------------------------------------------------------------------------------
  template<decorator D, typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cosh_
                                             , D const &
                                             , Z const& z
                                             ) noexcept
  requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
  {
    auto [rz, iz] = z;
    auto [s, c]   = sincos(iz);
    auto [sh, ch] = sinhcosh(rz);
    auto r = c*ch;
    auto i = s*sh;
    i = if_else(is_imag(z) || is_real(z), zero, i);
    auto res = Z(r, i);
    if constexpr(std::same_as<D, regular_type>) return res;
    else
    {
      if (eve::none(is_not_finite(z))) return res;
      res = if_else(is_infinite(rz) && is_not_finite(iz), Z(inf(as(rz)), nan(as(rz))), res);
      res = if_else(is_nan(rz) && is_infinite(iz),        Z(nan(as(rz)), nan(as(rz))), res);
      return res;
    }
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cosh_, Z const& z) noexcept
  {
    return cosh(regular_type(), z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== cos
  //===-------------------------------------------------------------------------------------------
  template<decorator D, typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cos_
                                             , D const & d, Z const& z) noexcept
  {
    Z iz{-imag(z), real(z)};
    return cosh(d, iz);
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cos_
                                             , pedantic_type const &, Z const& z) noexcept
  {
    return pedantic(cosh)(eve::i*z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cos_, Z const& z) noexcept
  {
    return cosh(eve::i*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== acosh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::acosh_
                                             , Z const& z) noexcept
  {
    // acosh(a0) = +/-i acos(a0)
    // Choosing the sign of multiplier to give nt2::real(acosh(a0)) >= 0
    // we have compatibility with C99.
    auto res = eve::acos(z);
    auto lez = is_lez(imag(res));
    res *= eve::i;
    return if_else(lez, res, -res);
  }

  //===-------------------------------------------------------------------------------------------
  //=== asinh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::asinh_
                                             , Z const& z) noexcept
  {
    return -(eve::i*asin(eve::i*z));
  }

  //===-------------------------------------------------------------------------------------------
  //=== atan
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::atan_
                                             , Z const& z) noexcept
  {
    // C99 definition here; atan(z) = -i atanh(iz):
    return -(eve::i*(eve::atanh(eve::i*z)));
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::exp_
                                             , Z const& z) noexcept
  {
    auto [rz, iz] = z;
    auto [s, c]   = sincos(iz);
    auto rho = exp(rz);
    return if_else(is_real(z) || rz == minf(as(rz)),
                   Z{rho, zero(as(rho))},
                   Z{rho*c, rho*s});
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp_i
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::exp_i_, Z const& z ) noexcept
  {
    return exp(eve::i*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp_ipi
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE  auto complex_unary_dispatch( eve::tag::exp_ipi_, Z const& z ) noexcept
  {
    auto [rz, iz] = eve::i*z;
    auto [s, c]   = sinpicospi(iz);
    auto rho = exp(rz*pi(as(rz)));
    return if_else(is_real(z) || rz == minf(as(rz)),
                   Z{rho, zero(as(rho))},
                   Z{rho*c, rho*s});
  }

  //===-------------------------------------------------------------------------------------------
  //=== log
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::log_
                                             , Z const& z) noexcept
  {
      auto argz = eve::arg(z);
      auto absz = if_else(is_nan(real(z)) && (inf(as(argz)) == imag(z)), inf(as(argz)), abs(z));
      return Z{log(absz), argz};
  }

  //===-------------------------------------------------------------------------------------------
  //=== log_abs
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::log_abs_
                                             , Z const& z) noexcept
  {
    return log(abs(z));
  }

  //===-------------------------------------------------------------------------------------------
  //=== rec
  //===-------------------------------------------------------------------------------------------

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::rec_
                                            , Z const& z ) noexcept
  {
    auto [a, b] = z;
    auto n2 = sqr_abs(z);
    return Z{a/n2, -b/n2};
  }

  //==============================================================================================
  //  Binary functions : ldexp ulpdist
  //==============================================================================================
  template<typename Z, integral_value N>
  EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::ldexp_
                                              , Z const& z1
                                              , N n
                                              ) noexcept
  {
    return as_wide_as_t<Z,N>(ldexp(real(z1), n), ldexp(imag(z1), n));
  }

  EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::ulpdist_
                                              , auto const& z1, auto const& z2
                                              ) noexcept
  {
    return eve::max ( eve::ulpdist(real(z1), real(z2))
                    , eve::ulpdist(imag(z1), imag(z2))
                    );
  }

}
