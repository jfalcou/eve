//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve::detail
{
  //===-------------------------------------------------------------------------------------------
  //  Unary functions : tgamma
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::tgamma_, Z const& a0) noexcept
  {
    // 15 sig. digits for 0<=real(z)<=171
    // coeffs should sum to about g*g/2+23/24
    //
    using r_t = element_type_t<as_real_t<Z>>;
    auto  g=r_t(607)/r_t(128);
    // best results when 4<=g<=5
    constexpr int N = 15;
    std::array<r_t, N>  c =
      {  0.99999999999999709182,
         57.156235665862923517,
         -59.597960355475491248,
         14.136097974741747174,
         -0.49191381609762019978,
         .33994649984811888699e-4,
         .46523628927048575665e-4,
         -.98374475304879564677e-4,
         .15808870322491248884e-3,
         -.21026444172410488319e-3,
         .21743961811521264320e-3,
         -.16431810653676389022e-3,
         .84418223983852743293e-4,
         -.26190838401581408670e-4,
         .36899182659531622704e-5
      };

    //Num Recipes used g=5 with 7 terms
    //for a less effective approximation

    auto negra0 = is_negative(real(a0));
    auto z = if_else(negra0, -a0, a0);
    z = dec(z);
    auto zh = z+half(as<r_t>());
    auto zgh=zh+g;
    //trick for avoiding FP overflow above z=141
    auto zp=pow(zgh,(zh*half(as<r_t>())));
    auto ss = Z{0, 0};
    for(int pp = N-1; pp >= 1; --pp){
      ss+= c[pp]/(z+pp);
    }
    auto sq2pi = r_t(2.5066282746310005024157652848110);
    auto f=(sq2pi*(c[0]+ss))*((zp*exp(-zgh))*zp);
    auto o = Z{1, 0};
    f = if_else(is_eqz(z) || z == o, o, f);
    //adjust for negative real parts
    auto reala0 = is_real(a0);
    if(any(negra0))
    {
      f = if_else(negra0, rec(-inv_pi(as(real(a0)))*a0*f*sinpi(a0)), zero);
      f = if_else (negra0 && reala0 && is_flint(real(a0)), Z{nan(as(sq2pi)), inf(as(sq2pi))}, f);
    }
    f = if_else(is_gtz(real(a0)) && is_flint(real(a0)) && reala0, Z{nearest(real(f)), 0}, f);
    f = if_else (is_eqz(a0), Z(inf(as(g))*pedantic(signnz)(real(a0)), 0), f);
    return f;
  }

  //===-------------------------------------------------------------------------------------------
  //  Unary functions : lgamma
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::lgamma_, Z const& a0) noexcept
  {
    // 15 sig. digits for 0<=real(z)<=171
    // coeffs should sum to about g*g/2+23/24
    //
    using r_t = element_type_t<as_real_t<Z>>;
    auto  g=r_t(607)/r_t(128);
    // best results when 4<=g<=5
    constexpr int N = 15;
    std::array<r_t, N>  c =
      {  0.99999999999999709182,
         57.156235665862923517,
         -59.597960355475491248,
         14.136097974741747174,
         -0.49191381609762019978,
         .33994649984811888699e-4,
         .46523628927048575665e-4,
         -.98374475304879564677e-4,
         .15808870322491248884e-3,
         -.21026444172410488319e-3,
         .21743961811521264320e-3,
         -.16431810653676389022e-3,
         .84418223983852743293e-4,
         -.26190838401581408670e-4,
         .36899182659531622704e-5
      };

    //Num Recipes used g=5 with 7 terms
    //for a less effective approximation

    auto negra0 = is_negative(real(a0));
    auto z = if_else(negra0, -a0, a0);
    auto ss = Z{0, 0};
    for(int pp = N-1; pp >= 1; --pp){
      ss += c[pp]*rec(z+dec(pp));
    }
    auto zg = z+g-half(as(g));
    auto lsq2pi = r_t(0.9189385332046727417803297);
    auto f=(lsq2pi + log(c[0]+ss)) - zg + (z-half(as<r_t>()))*log(zg);
    auto zer = Z{0, 0};
    auto o = Z{1, 0};
    auto t = Z{2, 0};
    f = if_else(z == t|| z == o, zer, f);
    //adjust for negative real parts
    if(any(negra0))
    {
      auto lpi = Z{1.14472988584940017414342735, pi(as(g))};
      auto reala0 = is_real(a0);
      f = if_else(negra0, lpi-log(a0)-f-log(sinpi(a0)), f);
      f = if_else (negra0 && reala0 && is_flint(real(a0)), Z{nan(as(g)), inf(as(g))}, f);
    }
    return f;
  }

    //===-------------------------------------------------------------------------------------------
  //  Unary functions : digamma
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::digamma_, Z const& a0) noexcept
  {
    // 15 sig. digits for 0<=real(z)<=171
    // coeffs should sum to about g*g/2+23/24
    //
    using r_t = element_type_t<as_real_t<Z>>;
    auto  g=r_t(607)/r_t(128);
    // best results when 4<=g<=5
    constexpr int N = 15;
    std::array<r_t, N>  c =
      {  0.99999999999999709182,
         57.156235665862923517,
         -59.597960355475491248,
         14.136097974741747174,
         -0.49191381609762019978,
         .33994649984811888699e-4,
         .46523628927048575665e-4,
         -.98374475304879564677e-4,
         .15808870322491248884e-3,
         -.21026444172410488319e-3,
         .21743961811521264320e-3,
         -.16431810653676389022e-3,
         .84418223983852743293e-4,
         -.26190838401581408670e-4,
         .36899182659531622704e-5
      };

    //Num Recipes used g=5 with 7 terms
    //for a less effective approximation

    auto reflection = real(a0) < half(as(real(a0)));
    auto z = if_else(reflection, oneminus(a0), a0);

    auto d = Z{0, 0};
    auto n = d;
    for(int pp = N-1; pp >= 1; --pp){
      auto dz = rec(z+dec(pp));
      auto dd =  c[pp]*dz;
      d += dd;
      n -= dd*dz;
    }
    d+= c[0];
    auto zg = z+g-half(as(g));
    auto f = log(zg) + (n/d - g/zg);

    if(any(reflection))
    {
      f = if_else(reflection, f-pi(as(g))*cotpi(a0), f);
      f = if_else (reflection && is_real(a0) && is_flint(real(a0)), Z{nan(as(g)), inf(as(g))}, f);
    }
    return f;
  }
 }
