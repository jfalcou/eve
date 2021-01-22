//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fnms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/real/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cot_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
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
      return apply_over(restricted(cot), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cot_(EVE_SUPPORTS(cpu_), small_type const &, T a0) noexcept
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
      return apply_over(small(cot), a0);
  }

  //////////////////////////////////////////////////////////////////
  /// medium,  big
  // why the hell the typename can not be typename as in cos ?
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr T cot_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
        if( is_not_finite(a0) )
          return nan(eve::as<T>());
      const T x = abs(a0);
      if constexpr( scalar_value<T> )
        if( x < eps(as<T>()) )
          return rec(a0);
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
      if( eve::all(x <= pio_4(eve::as(x))) )
        return restricted(cot)(a0);
      else if( eve::all(x <= pio_2(eve::as(x))) )
        return small(cot)(a0);
      else if( eve::all(x <= Rempio2_limit(eve::medium_type(), as(a0))) )
        return medium(cot)(a0);
      else
        return big(cot)(a0);
    }
    else
      return apply_over(cot, a0);
  }
}
