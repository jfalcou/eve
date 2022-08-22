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

namespace eve
{
  namespace detail
  {
    template < typename Z1,  typename Z2>
    EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::pow_
                                                , Z1 const& z1, Z2 const& z2
                                                ) noexcept
    requires(floating_value<element_type_t<Z2>> || is_complex_v<Z2>)
    {
      using r_t = decltype(z1+z2);
      r_t r;
      if constexpr(floating_value<Z1> ) // z2 is complex z1 is real
      {
        auto [rz2, iz2] = z2;
        auto lgaz1 = log_abs(z1);
        auto arg = if_else(is_real(z2), zero, iz2*lgaz1);
        auto mod = pow(z1, rz2);
        auto r1 = polar(mod, arg);
        auto isposz1 = is_positive(z1);
        if (eve::all(isposz1))
        {
          r = r1;
        }
        else
        {
          auto rho = exp(diff_of_prod(lgaz1, rz2, iz2, pi(as(rz2))));
          auto theta = pedantic(sum_of_prod)(pi(as(rz2)), rz2, iz2, lgaz1);
          auto r2 = rho*exp_i(theta);
          r = if_else(isposz1, r1, r2);
        }
      }
      else if constexpr(floating_value<Z2> ) // z1 is complex z2 is real
      {
        auto flintz2 = is_flint(z2);
        if (any(flintz2)) r = eve::pow(z1, int_(z2));
        auto lz1 = log_abs(z1);
        auto argz1 = pedantic(arg)(z1);
        auto rho = exp(lz1*z2);
        auto theta = argz1*z2;
        r = if_else(flintz2, r, rho*exp_i(theta));
      }
      else  // z1 and z2 are complex
      {
        auto [rz2, iz2] = z2;
        auto lz1 = log_abs(z1);
        auto argz1 = pedantic(arg)(z1);
        auto rho = exp(pedantic(diff_of_prod)(lz1, rz2, iz2, argz1));
        auto theta = pedantic(sum_of_prod)(argz1, rz2, iz2, lz1);
        r = rho*exp_i(theta);
        auto realz1 = is_real(z1);
        if(any(realz1))
        {
          auto rr = to_complex(pow(real(z1), z2));
          r = if_else(realz1, rr, r);
        }
      }
      r = if_else(is_eqz(z2),  r_t{1, 0}, r);
     return r;
    }
  }
}
