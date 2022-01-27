//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/constant/twoopi.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cot_(EVE_SUPPORTS(cpu_), quarter_circle_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto aa0nlepio4 = is_not_less_equal(eve::abs(a0), pio_4(eve::as<T>()));
      if constexpr( scalar_value<T> )
      {
        return (aa0nlepio4) ? nan(eve::as<T>()) : rec(tancot_eval(a0));
      }
      else
      {
        return if_else(aa0nlepio4, eve::allbits, rec(tancot_eval(a0)));
      }
    }
    else
      return apply_over(quarter_circle(cot), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cot_(EVE_SUPPORTS(cpu_), half_circle_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T    x      = eve::abs(a0);
      auto xleeps = x <= eps(as<T>());
      auto reduce = [](auto x) {
        auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
        auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
        auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
        auto xr     = x - pio2_1;
        xr -= pio2_2;
        xr -= pio2_3;
        return xr;
      };
      if constexpr( scalar_value<T> )
      {
        using i_t =  as_integer_t<T, signed>;
        if (xleeps) return rec(a0);
        if (is_not_less_equal(x, pio_2(eve::as<T>()))) return nan(eve::as<T>());
        i_t n = x > pio_4(eve::as<T>());
        if( n )
        {
          auto xr = reduce(x);
          T    y  = tancot_eval(xr);
          return bit_xor(bitofsign(a0), -y);
        }
        else
        {
          return rec(tancot_eval(a0));
        }
      }
      else
      {
        auto xnlepio4 = is_not_less_equal(x, pio_4(eve::as(x)));
        auto fn       = binarize(xnlepio4);
        auto xr       = if_else(fn, reduce(x), x);
        auto y        = tancot_eval(xr);
        y             = if_else(is_not_finite(a0), eve::allbits, if_else(xnlepio4, -y, rec(y)));
        return if_else(xleeps, rec(a0), bit_xor(bitofsign(a0), y));
      }
    }
    else
      return apply_over(half_circle(cot), a0);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr T cot_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<full_circle_type, medium_type, big_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x         = abs(a0);
      auto xnlelim   = is_not_less_equal(x, Rempio2_limit(D(), as(a0)));
      if constexpr( scalar_value<T> )
      {
        if( xnlelim ) return nan(eve::as<T>());
      }
      else
        x = if_else(xnlelim, allbits, x);
      auto [fn, xr, dxr] = D()(rempio2)(x);
      return cot_finalize(a0, fn, xr, dxr);
    }
    else
      return apply_over(D()(cot), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cot_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = eve::abs(a0);
      if( eve::all(x <= Rempio2_limit(quarter_circle_type(), as(a0))))
        return quarter_circle(cot)(a0);
      else if( eve::all(x <= Rempio2_limit(half_circle_type(), as(a0))))
        return half_circle(cot)(a0);
      else if( eve::all(x <=  Rempio2_limit(full_circle_type(), as(a0))))
        return full_circle(cot)(a0);
      else if( eve::all(x <= Rempio2_limit(medium_type(), as(a0))))
        return medium(cot)(a0);
      else
        return big(cot)(a0);
    }
    else
      return apply_over(cot, a0);
  }
}
