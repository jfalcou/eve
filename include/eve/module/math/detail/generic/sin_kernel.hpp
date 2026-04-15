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
  struct sin_kernel_t : elementwise_callable<sin_kernel_t, Options, quarter_circle_option,
                                             half_circle_option, full_circle_option,
                                             medium_option, big_option,
                                             rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sin_kernel_t, sin_kernel_);
  };

  inline constexpr auto sin_kernel = functor<sin_kernel_t>;

}

namespace eve::_
{
  template<floating_value T, callable_options O> EVE_NOINLINE
  T sin_kernel_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
  {
    if constexpr(O::contains(deg))
    {
      auto x = eve::abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        return  sin_kernel[radpi][eve::quarter_circle](div_180(a0));
      }
      else
      {
        if( eve::all(eve::abs(x) <= T(45)) )  return sin_kernel[deg][quarter_circle](a0);
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
        x                  = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
        auto [fn, xr, dxr] = rem180(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
    }
    else if constexpr(O::contains(radpi))
    {
      if constexpr(O::contains(quarter_circle))
      {
        return sin_kernel[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        if( eve::all(x <= T(0.25)) )
          return sin_kernel[radpi][quarter_circle](a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return T(0);
        }
        else
        {
          x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
          x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
    }
    else
    {
      if constexpr(O::contains(quarter_circle))
      {
        auto pi2_16 = pi2o_16[upper](as<T>());
        auto x2 = sqr(a0);
        if constexpr( scalar_value<T> )
          if( is_not_less_equal(x2, pi2_16) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        auto r = bit_xor(sin_eval(x2, x), bitofsign(a0));
        if constexpr( scalar_value<T> ) return r;
        else return if_else(is_not_less_equal(x2, pi2_16), eve::allbits, r);
      }
      else if constexpr(O::contains(half_circle))
      {
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921fb54400000p+0 , 0x1.921f000p+0f >(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.0b4611a600000p-34, 0x1.6a88000p-17f>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.3198a2e000000p-69, 0x1.0b46000p-34f>(eve::as<T>{});
            T    xr     = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        auto x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;
          if( is_less_equal(x, eps(as<T>())) ) return a0;
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          i_t n = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            return bit_xor(bitofsign(a0), cos_eval(sqr(xr)));
          }
          else return sin_eval(sqr(x), a0);
        }
        else
        {
          auto n     = is_not_less_equal(x, pio_4(eve::as<T>()));
          auto xr    = reduce(x);
          xr         = if_else(n, xr, x);
          const T z  = sqr(xr);
          const T se = sin_eval(z, xr);
          const T ce = cos_eval(z);
          const T z1 = bit_xor(bitofsign(a0), if_else(n, ce, se));
          return if_else(is_not_less_equal(x, pio_2(eve::as<T>())), nan(eve::as<T>()), z1);
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto x       = abs(a0);
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return sin_finalize(a0, fn, xr, dxr);
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return sin_kernel[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return sin_kernel[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return sin_kernel[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return sin_kernel[medium](a0);
        else
          return sin_kernel[big](a0);
      }
    }
  }
}
