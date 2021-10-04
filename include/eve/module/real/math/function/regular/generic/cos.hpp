//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/real/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); // 0.61685027506808491367715568749226
                                                                            // but rounded upward
      auto x2          = sqr(a0);
      auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
      if constexpr( scalar_value<T> )
        return (x2nlepi2_16) ? nan(eve::as<T>()) : cos_eval(x2);
      else
        return if_else(x2nlepi2_16, eve::allbits, cos_eval(x2));
    }
    else
      return apply_over(restricted(cos), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_), small_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T    x        = eve::abs(a0);
      auto xnlepio2 = is_not_less_equal(x, pio_2(eve::as<T>()));
      if constexpr( scalar_value<T> )
        if( xnlepio2 )
          return nan(eve::as<T>());
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
        using i_t = as_integer_t<T, signed>;
        i_t n     = x > pio_4(eve::as<T>());
        if( n )
        {
          auto xr = reduce(x);
          return bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1));
        }
        else
          return cos_eval(sqr(x));
      }
      else
      {
        using elt_t   = element_type_t<T>;
        auto n        = binarize(is_not_less_equal(x, pio_4(eve::as(x))));
        auto sign_bit = binarize(is_nez(n), signmask(eve::as<elt_t>()));
        auto xr       = reduce(x);
        xr            = if_else(n, xr, x);
        auto z        = sqr(xr);
        auto se       = bit_xor(sin_eval(z, xr), sign_bit);
        auto ce       = cos_eval(z);
        auto z1       = if_else(n, se, ce);
        return if_else(xnlepio2, eve::allbits, z1);
      }
    }
    else
      return apply_over(small(cos), a0);
  }

  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  requires(is_one_of<D>(types<circle_type, medium_type, big_type> {}))
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
      return cos_finalize(fn, xr, dxr);
    }
    else
      return apply_over(D()(cos), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( eve::all(x <= Rempio2_limit(restricted_type(), as(a0))))
        return restricted(cos)(a0);
      else if( eve::all(x <= Rempio2_limit(small_type(), as(a0))))
        return small(cos)(a0);
      else if( eve::all(x <=  Rempio2_limit(circle_type(), as(a0))))
        return circle(cos)(a0);
      else if( eve::all(x <= Rempio2_limit(medium_type(), as(a0))))
        return medium(cos)(a0);
      else
        return big(cos)(a0);
    }
    else
      return apply_over(cos, a0);
  }

}
