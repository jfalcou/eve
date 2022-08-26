//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/complex/regular/traits.hpp>
#include <iostream>

namespace eve
{
  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::erf_, Z const& z) noexcept
    {
      using v_t = eve::as_real_t<Z>;
      using real_t = eve::element_type_t<v_t>;
      if constexpr (sizeof(real_t) == 4) {
        auto [x, y] = z;
        auto dx =  float64(x);
        auto dy =  float64(y);
        using dr_t = decltype(dx);
        using dc_t = as_complex_t<dr_t>;
        dc_t dz(dx, dy);
        auto r = erf(dz);
        return Z(real(r), imag(r));
      }
      auto az =  sqr_abs(z);
      auto large = az > 64;
      auto c_small = [](auto z){
        constexpr size_t nn = 32;
        auto[x, y] = z;
        auto k1 = two_o_pi(as(x)) * expx2(x, mone(as(x)));
        auto k2 = exp_i(-2*x*y);
        auto s1 = erf(x);
        auto isnezx = is_nez(x);
        auto s2 = if_else(isnezx, k1/(4*x)*oneminus(k2), i(as(z))*(inv_pi(as(y))/y));
        auto f = s1 + s2;
        auto isnezy = is_nez(y);
        auto s5 = zero(as(z));
        for(real_t n = 1; n <= nn;  n = inc(n))
        {
          auto n2 = sqr(n);
          auto s3 = exp(-n2*real_t(0.25))/fma(4*x, x, n2);
          auto [sh, ch] = sinhcosh(n*y);
          auto s4 = 2*x - k2*Z(2*x*ch, -n*sh);
          s5 = s5 + s3*s4;
        }
        auto s6 = k1* s5;
        f =  if_else(isnezy, f + s6, f);
        return f;
      };

      auto c_large = [](auto z){
        auto isltzrz= is_ltz(real(z));
        z = if_else(isltzrz, -z, z);
        constexpr size_t nmax=193;
        auto s=one(as(z));
        auto y=2*sqr(z);
        auto ry = rec(y);
        for (int n = nmax; n >= 1; n-= 2)  s=oneminus(n*(s*ry));
        auto f=oneminus(s*exp(-sqr(z))/(sqrt_pi(as(real(z)))*z));
        f = if_else(isltzrz, -f, f);

        auto isimagz = is_imag(z);
        f =  if_else(isimagz, dec(f), f);
        return f;
      };
      if(eve::all(large)) return c_large(z);
      else if (eve::none(large)) return c_small(z);
      else return if_else(large, c_large(z), c_small(z));
    }
  }
}
