//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/constant/pi.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/regular/deginrad.hpp>


namespace eve
{
  template<typename Options>
  struct cot_kernel_t : elementwise_callable<cos_kernel_t, Options, quarter_circle_option,
                                             half_circle_option, full_circle_option,
                                             medium_option, big_option,
                                             rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cot_kernel_t, cot_kernel_);
  };

  inline constexpr auto cot_kernel = functor<cot_kernel_t>;

}

namespace eve::detail
{
  template<floating_value T, callable_options O>
  T cot_kernel_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
  {
    if constexpr(O::contains(deg))
    {
      auto x = abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          if( is_not_less_equal(x, T(45)) ) return nan(eve::as<T>());
          return rec[pedantic](tancot_eval(deginrad(a0)));
        }
        else
        {
          return if_else(
            is_eqz(a0),
            bit_or(a0, inf(eve::as(a0))),
            if_else(is_not_less_equal(x, T(45)), eve::allbits, rec[pedantic](tancot_eval(deginrad(a0)))));
        }
      }
      else
      {
        if( eve::all(x <= T(45)) ) return cot_kernel[deg][quarter_circle](a0);
        T    a0_180 = div_180(a0);
        auto test   = is_nez(a0_180) && is_flint(a0_180);
        if constexpr( scalar_value<T> ) // early return for nans in scalar case
        {
          if( test ) return nan(eve::as<T>());
        }
        else { x = if_else(test, eve::allbits, x); }
        auto [fn, xr, dxr] = rem180(x);
        return cot_finalize(deginrad(a0), fn, xr, dxr);
      }
    }
    else if constexpr(O::contains(radpi))
    {
      if constexpr(O::contains(quarter_circle))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          auto x = abs(a0);
          if( is_not_less_equal(x, T(0.25)) ) return nan(eve::as<T>());
          return rec[pedantic](tancot_eval(pi(eve::as<T>()) * a0));
        }
        else
        {
          auto x = eve::abs(a0);
          return if_else(is_eqz(a0),
                         bit_or(a0, inf(eve::as(a0))),
                         if_else(is_not_less_equal(x, T(0.25)),
                                 eve::allbits,
                                 rec[pedantic](tancot_eval(pi(eve::as<T>()) * a0))));
        }
      }
      else
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
          if( is_not_finite(a0) || is_flint(a0) ) return nan(eve::as<T>());
        }
        auto x = abs(a0);
        if( eve::all(x <= T(0.25)) ) return cot_kernel[radpi][quarter_circle](a0);
        if constexpr( simd_value<T> )
        {
          x = if_else(is_not_finite(a0) || is_flint(x), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return cot_finalize(a0 * pi(eve::as<T>()), quadrant(fn), xr, dxr);
      }
    }
    else
    {
      auto x =  eve::abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        auto aa0nlepio4 = is_not_less_equal(x, pio_4(eve::as<T>()));
        if constexpr( scalar_value<T> )
        {
          return (aa0nlepio4) ? nan(eve::as<T>()) : rec[pedantic](tancot_eval(a0));
        }
        else { return if_else(aa0nlepio4, eve::allbits, rec[pedantic](tancot_eval(a0))); }
      }
      else if constexpr(O::contains(half_circle))
      {
        auto xleeps = x <= eps(as<T>());
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921fb54400000p+0,  0x1.921f000p+0f >(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.0b4611a600000p-34, 0x1.6a88000p-17f>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.3198a2e000000p-69, 0x1.0b46000p-34f>(eve::as<T>{});
            auto xr     = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;
          if( xleeps ) return rec[pedantic](a0);
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          i_t n = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            T    y  = tancot_eval(xr);
            return bit_xor(bitofsign(a0), -y);
          }
          else { return rec[pedantic](tancot_eval(a0)); }
        }
        else
        {
          auto xnlepio4 = is_not_less_equal(x, pio_4(eve::as(x)));
          auto fn       = one[xnlepio4](eve::as(x));
          auto xr       = if_else(fn, reduce(x), x);
          auto y        = tancot_eval(xr);
          y             = if_else(is_not_finite(a0), eve::allbits, if_else(xnlepio4, -y, rec[pedantic](y)));
          return if_else(xleeps, rec[pedantic](a0), bit_xor(bitofsign(a0), y));
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return cot_finalize(a0, fn, xr, dxr);
      }
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return cot_kernel[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return cot_kernel[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return cot_kernel[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return cot_kernel[medium](a0);
        else
          return cot_kernel[big](a0);
      }
    }
  }
}
