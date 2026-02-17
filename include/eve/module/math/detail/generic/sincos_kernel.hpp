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

namespace eve
{
  template<typename Options>
  struct sincos_kernel_t : elementwise_callable<sincos_kernel_t, Options, quarter_circle_option,
                                             half_circle_option, full_circle_option,
                                             medium_option, big_option,
                                             rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sincos_kernel_t, sincos_kernel_);
  };

  inline constexpr auto sincos_kernel = functor<sincos_kernel_t>;

}

namespace eve::detail
{
  template<floating_value T, callable_options O> EVE_NOINLINE
  zipped<T,T> sincos_kernel_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
  {
    if constexpr(O::contains(deg))
    {
      if constexpr(O::contains(quarter_circle))
      {
        return sincos_kernel[radpi][eve::quarter_circle](div_180(a0));
      }
      else
      {
        if( eve::all(eve::abs(a0) <= T(45)) ) return sincos_kernel[deg][quarter_circle](a0);
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        auto x             = eve::abs(a0);
        x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        auto[s,c] = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s,c);
      }
    }
    else if constexpr(O::contains(radpi))
    {
      if constexpr(O::contains(quarter_circle))
      {
        return sincos_kernel[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        if constexpr( scalar_value<T> )
        {
          if( is_not_finite(a0) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        }
        T x = abs(a0);
        if( eve::all(x <= T(0.25)) )  return sincos_kernel[radpi][quarter_circle](a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return eve::zip(T(0), T(1));
        }
        else
        {
          auto invalid = is_not_finite(x);
          x            = if_else(x > maxflint(eve::as(x)), eve::zero, x);
          x            = if_else(invalid, eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s, c);
      }
    }
    else
    {
      auto x       = abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        auto pi2_16 = pi2o_16[upper](as<T>());
        auto x2          = sqr(a0);
        auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
        if constexpr( scalar_value<T> )
        {
          return  (x2nlepi2_16) ? eve::zip(nan(eve::as<T>()), nan(eve::as<T>()))
            : eve::zip(sin_eval(x2, a0), cos_eval(x2));
        }
        else
        {
          x2 = if_else(x2nlepi2_16, eve::allbits, x2);
          return eve::zip(sin_eval(x2, a0), cos_eval(x2));
        }
      }
      else if constexpr(O::contains(half_circle))
      {
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921fb54400000p+0 , 0x1.921f000p+0f >(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.0b4611a600000p-34, 0x1.6a88000p-17f>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.3198a2e000000p-69, 0x1.0b46000p-34f>(eve::as<T>{});

            T xr = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;

            return xr;
          };

        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;

          if( is_less_equal(x, eps(as<T>())) ) return eve::zip(a0, one(eve::as<T>()));
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));

          i_t n = x > pio_4(eve::as<T>());

          if( n )
          {
            auto xr = reduce(x);
            return eve::zip ( bit_xor(bitofsign(a0), cos_eval(sqr(xr)))
                            , bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1))
                            );
          }
          else return eve::zip(sin_eval(sqr(x), a0), cos_eval(sqr(x)));
        }
        else
        {
          x           = if_else(is_not_less_equal(x, pio_2(eve::as<T>())), eve::allbits, x);
          auto test   = is_not_less_equal(x, pio_4(eve::as<T>()));
          auto n      = one[test](eve::as(x));
          auto xr     = if_else(test, reduce(x), x);
          auto [s, c] = sincos_finalize(a0, n, xr, T(0));
          return eve::zip(s, c);
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s, c);
      }
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )   return sincos_kernel[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))  return sincos_kernel[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))  return sincos_kernel[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))       return sincos_kernel[medium](a0);
        else                                                         return sincos_kernel[big](a0);
      }
    }
  }
}
