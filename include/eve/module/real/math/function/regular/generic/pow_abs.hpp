//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/real/math/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <eve/function/modf.hpp>
#include <eve/function/converter.hpp>

#include <concepts>
#include <cmath>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_),
                                T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pow_abs, a, b);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(raw(pow_abs), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  pow_abs_(EVE_SUPPORTS(cpu_), raw_type const &, T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return eve::exp(b * eve::log(eve::abs(a)));
    }
    else return apply_over(raw(pow_abs), a, b);
  }

  template<floating_real_value T>
  auto pow_abs_(EVE_SUPPORTS(cpu_), T x, T y) noexcept
  {
    if constexpr(scalar_value<T>) return std::pow(eve::abs(x), y);
    if constexpr(has_native_abi_v<T>)
    {
      using i_t = as_integer_t<T, unsigned>;
      using eli_t = element_type_t<i_t>;
      auto iseqzx = is_eqz(x);
      auto ylt0 = y < zero(as(y));
      auto ax = eve::abs(x);
      auto ax_is1 = ax == eve::one(as(x));
      eli_t const largelimit = (sizeof(eli_t) == 4 ? 31 : 63);
      auto [yf,  yi] = eve::modf(eve::abs(y));
      auto test =  yf > T(0.5);
      yf = dec[test](yf);
      auto z = eve::exp(yf * eve::log(ax));
      yi = inc[test](yi);
      yi = if_else(ax_is1, eve::one, yi);
      auto large = (yi > T(largelimit));
      yi =  if_else(large, eve::one, yi);

      auto russian = [](T base, i_t expo){
        T result(1);
        while( eve::any(is_nez(expo)) )
        {
          result *= if_else(is_odd(expo), base, T(1));
          expo = (expo >> 1);
          base = sqr(base);
        }
        return result;
      };
      z *= russian(ax, uint_(yi));
      z =  if_else(large, if_else(ax < one(as(x)), zero, inf(as(x))), z);
      z =  if_else(iseqzx && ylt0, zero, z);
      z =  if_else(is_infinite(ax), inf(as(x)), z);
      z =  if_else(ylt0, rec(z), z);
      z =  if_else(ax_is1 || is_eqz(y), one, z);
      z =  if_else(iseqzx && is_gtz(y), zero, z);
      z =  if_else(is_nan(x) && is_nan(y), allbits, z);
      return z;
    }
    else return apply_over(pow_abs, x, y);
  }
}
