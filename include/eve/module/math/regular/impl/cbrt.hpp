//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cbrt_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using vt_t =  element_type_t<T>;
      auto test0 = is_eqz(x) || is_not_finite(x);
      if constexpr(scalar_value<T>) if(test0) return x;
      constexpr vt_t factor[5] = {0.6299605249474365823836, 0.793700525984099737376, 1.0
                                , 1.2599210498948731647672, 1.587401051968199474751};
      auto ax = eve::abs (x);
      auto test = is_less(eve::abs(x), T(100)*smallestposval(eve::as<T>()));
      ax = if_else(test, ldexp(ax, 54), ax);
      /* Reduce x.  xm now is an range  [0.5, 1.0].  */
      auto [xm, xe] = raw(ifrexp)(ax);
      T u;
      if constexpr(std::is_same_v<vt_t, double>)
      {
        u = horn<T, 0x3fd6b69cba168ff2ll, 0x3ff8218dde9028b4ll, 0xc000eb8277cd8d5dll, 0x40039350adad51ecll,
                    0xbffd5ae6cfa20f0cll, 0x3fe91e2a6fe7e984ll, 0xbfc29801e893366dll  >(xm);
      }
      else if constexpr(std::is_same_v<vt_t, float>)
      {
        u = horn <T, 0x3efc3de2, 0x3f3293fa, 0xbe441925>(xm);
      }
      auto t2 = sqr(u) * u;
      u *= fma(xm, T(2), t2) / fma(T(2), t2, xm);

      if constexpr(scalar_value<T>) u *= factor[2 + xe % 3];
      else                          u *= gather(&factor[0], 2 + xe-(xe/3)*3);
      u = minus[is_ltz(x)](u);
      if constexpr(scalar_value<T>)   xe = add[test](int(xe)/3, -18);
      else                            xe = add[test](xe/3, -18);
      auto z = ldexp(u, xe);
      if constexpr(scalar_value<T>) return z;
      else                          return if_else(test0, x, z);
    }
    else return apply_over(cbrt, x);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_value U>
  EVE_FORCEINLINE auto cbrt_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::cbrt, t);
  }

}
