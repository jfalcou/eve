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
  // sqrt cosh cos acosh asinh atan exp exp_i exp_ipi log rec are here.
  // acos asin atanh are in specific files included at the end
  //==============================================================================================

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : sqrt
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::sqrt_
                                             , Z const& z
                                              ) noexcept
  {
    //always compute the sqrt of the complex with positive imaginary part
    //then conjugate if necessary
    auto [rz, iz] = z;
    auto negimag = is_negative(iz);
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
    if (any(is_not_finite(z))) [[unlikely]]
    {
      res = if_else(rz == minf(as(rz))
                   , if_else( is_nan(iz), Z{iz, minf(as(rz))},Z{zero(as(rz)), inf(as(rz))})
                   , res
                   );
       res = if_else(rz == inf(as(rz))
                   , if_else( is_nan(iz), Z{inf(as(rz)), iz}, Z{ inf(as(rz)), zero(as(rz)) })
                   , res
                   );
       res = if_else(is_nan(rz), Z{rz, rz}, res);
       auto infty = inf(as(iaz));
       res = if_else(iaz == infty,  Z{infty, infty}, res);
    }
    return if_else(negimag, conj(res), res);
 }

  //===-------------------------------------------------------------------------------------------
  //=== cosh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cosh_
                                             , Z const& z
                                             ) noexcept
  {
    auto [rz, iz] = z;
    auto [s, c]   = sincos(iz);
    auto [sh, ch] = sinhcosh(rz);
    auto r = c*ch;
    auto i = s*sh;
    i = if_else(is_imag(z) || is_real(z), zero, i);
    auto res = Z(r, i);
    if (any(is_not_finite(z)))
    {
      res = if_else(is_infinite(rz) && is_not_finite(iz), Z(inf(as(rz)), nan(as(rz))), res);
      res = if_else(is_nan(rz) && is_infinite(iz),        Z(nan(as(rz)), nan(as(rz))), res);
    }
    return res;
  }

  //===-------------------------------------------------------------------------------------------
  //=== sinh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::sinh_
                                             , Z const& z
                                             ) noexcept
  {
    auto [rz, iz] = z;
    auto [s, c]   = sincos(iz);
    auto [sh, ch] = sinhcosh(rz);
    auto r = c*sh;
    auto i = s*ch;
    if (eve::all(is_finite(z))) return Z{r, i};
    auto infrz = is_infinite(rz);
    auto nanrz = is_nan(rz);
    r = if_else(infrz && is_not_finite(iz), rz, r);
    i = if_else(infrz && is_nan(iz), allbits, i);
    r = if_else(nanrz, allbits, r);
    i = if_else(nanrz, allbits, i);
    i = if_else(is_real(z), zero, i);
    r = if_else(is_imag(z), zero, r);
    return Z{r, i};
  }

  //===-------------------------------------------------------------------------------------------
  //=== tanh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::tanh_
                                             , Z const& z
                                             ) noexcept
  {
    auto zz = z+z;
    auto [rz, iz] = zz;
    auto [s, c] = sincos(iz);
    auto [sh, ch] = sinhcosh(rz);
    auto tmp = c+ch;
    auto rr = if_else(is_imag(z), zero, sh/tmp);
    auto ii = if_else(is_real(z), zero, s/tmp);
    return if_else(is_infinite(rz), Z{sign(rz), 0}, Z{rr, ii});
  }

  //===-------------------------------------------------------------------------------------------
  //=== cos
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::cos_, Z const& z) noexcept
  {
    return cosh(eve::i(as(z))*z);
  }


  //===-------------------------------------------------------------------------------------------
  //=== sin
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::sin_
                                             , Z const& z) noexcept
  {
    auto j = i(as(z));
    return -(j*sinh(j*z));
  }

  //===-------------------------------------------------------------------------------------------
  //=== tan
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::tan_
                                             , Z const& z
                                             ) noexcept
  {
    auto j = eve::i(as(z));
    return -j*eve::tanh(j*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== acosh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::acosh_
                                             , Z const& z) noexcept
  {
    // acosh(a0) = +/-i acos(a0)
    // Choosing the sign of multiplier to give real(acosh(a0)) >= 0
    // we have compatibility with C99.
    auto res = eve::acos(z);
    auto lez = is_negative(imag(res));
    res *= eve::i;
    auto nani = is_nan(imag(z));
    res = if_else(lez, res, -res);
    if (any(nani))
      return if_else(nani && is_finite(real(z)), Z{nan(as(real(z))), nan(as(real(z)))}, res);
    else
      return res;
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
    return  -(eve::i*(eve::atanh(eve::i*z)));
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
    auto rho = if_else(is_nan(rz), allbits, eve::exp(rz));
    auto res = if_else(is_real(z) || rz == minf(as(rz)),
                       Z{rho, zero(as(rho))},
                       Z{rho*c, rho*s});
    return if_else(rz == inf(as(rz)) && is_not_finite(iz), Z{rz, nan(as(iz))}, res);
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp2
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::exp2_
                                             , Z const& z) noexcept
  {
    return exp(log_2(as(real(z)))*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp10
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::exp10_
                                             , Z const& z) noexcept
  {
    return exp(log_10(as(real(z)))*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== expm1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::expm1_
                                             , Z const& z) noexcept
  {
    auto u =  exp(z);
    auto w =  dec(u); 
    auto ru =  real(u);
    auto exceptionnal = (is_eqz(ru) ||(is_not_finite(u) || is_eqz(z)
                                       || is_nan(z)
                                       || is_not_less(abs(imag(z)), pio_2(as(imag(z))))));
    auto correct = z/log1p(w);
    auto real_case = Z{expm1(real(z)), zero(as(real(z)))};
    return  if_else(is_real(z), real_case, if_else(exceptionnal, w, w*correct));
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp_i
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::exp_i_, Z const& z ) noexcept
  {
    return exp(eve::i(as<Z>())*z);
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp_ipi
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE  auto complex_unary_dispatch( eve::tag::exp_ipi_, Z const& z ) noexcept
  {
    auto [rz, iz] = eve::i(as<Z>())*z;
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
    auto [rz, iz] = z;
    auto infty = inf(as(rz));
    auto argz = pedantic(eve::arg)(z);
    auto absz = if_else(is_nan(rz) && is_infinite(iz), infty, abs(z));
    auto la = log(absz);
    auto r = if_else(is_real(z) && is_positive(rz), Z{la, zero(as(rz))}, Z{la, argz});
    if(eve::any(is_not_finite(z)))
    {
      r = if_else(is_eqz(z)
                 , Z{minf(as(rz)), if_else(is_positive(rz), zero, pedantic(signnz)(iz)*pi(as(rz)))}
                 , r);
      r = if_else(is_infinite(rz) && is_nan(iz), Z{infty, iz}, r);
    }
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //=== log10
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::log10_
                                             , Z const& z) noexcept
  {
    auto [rz, iz] = z;
    auto infty = inf(as(rz));
    auto argz = pedantic(eve::arg)(z)/log_10(as(rz));
    auto absz = if_else(is_nan(rz) && is_infinite(iz), inf(as(argz)), abs(z));
    auto la = log10(absz);
    auto r = if_else(is_real(z) && is_positive(rz), Z{la, zero(as(rz))}, Z{la, argz});
    if(eve::any(is_not_finite(z)))
    {
      r = if_else(is_eqz(z)
                 , Z{minf(as(rz)), if_else(is_positive(rz), zero, pedantic(signnz)(iz)*pi(as(rz))/log_10(as(rz)))}
                 , r);
      r = if_else(is_infinite(rz) && is_nan(iz), Z{infty, iz}, r);
    }
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //=== log2
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::log2_
                                             , Z const& z) noexcept
  {
    auto [rz, iz] = z;
    auto infty = inf(as(rz));
    auto argz = pedantic(eve::arg)(z)/log_2(as(rz));
    auto absz = if_else(is_nan(real(z)) && (is_infinite(iz)), inf(as(argz)), abs(z));
    auto la = log2(absz);
    auto r = if_else(is_real(z) && is_positive(rz), Z{la, zero(as(rz))}, Z{la, argz});
    if(eve::any(is_not_finite(z) || is_eqz(z)))
    {
      r = if_else(is_eqz(z)
                 , Z{minf(as(rz)), if_else(is_positive(rz), zero, pedantic(signnz)(iz)*pi(as(rz))/log_2(as(rz)))}
                 , r);
      r = if_else(is_infinite(rz) && is_nan(iz), Z{infty, iz}, r);
    }
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //=== log1p
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::log1p_
                                             , Z const& z) noexcept
  {
    auto m = inc(z);
    auto theta = if_else((is_real(m) && is_nltz(real(m))), zero, arg(m)) ;
    auto rz =  real(z);
    auto iz2 =  sqr(imag(z));
    using r_t = decltype(rz);

    return Z{half(as<r_t>())*log1p(rz*(rz+r_t(2))+iz2), theta};
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

#include <eve/module/complex/regular/detail/acos.hpp>
#include <eve/module/complex/regular/detail/asin.hpp>
#include <eve/module/complex/regular/detail/atanh.hpp>
