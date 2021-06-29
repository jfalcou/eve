//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
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
  requires(has_native_abi_v<T>)
  {
    return eve::exp(b * eve::log(eve::abs(a)));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_), T x, T y) noexcept
  requires has_native_abi_v<T>
  {
    using i_t = as_integer_t<T, unsigned>;
    using eli_t = element_type_t<i_t>;
    auto iseqzx = is_eqz(x);
    auto ylt0 = y < zero(as(y));
    auto ax = eve::abs(x);
    auto ax_is1 = ax == eve::one(as(x));
    if constexpr(real_scalar_value<T> )
    {
      if(iseqzx && ylt0) return inf(as(x));
      if(is_infinite(ax)) return y == 0 ? T(1) : (ylt0 ? T(0) : inf(as(x)));
      if(y == minf(as(y)))  return (ax == T(1)) ? T(1) : (ax > T(1)) ? T(0) : inf(as(y));
      if(ax_is1 || is_eqz(y)) return T(1);
      if(iseqzx && is_gtz(y)) return T(0);
    }
    eli_t const largelimit = (sizeof(eli_t) == 4 ? 31 : 63);
    auto [yf,  yi] = eve::modf(eve::abs(y));
    auto test =  yf > T(0.5);
    yf = dec[test](yf);
    auto z = eve::exp(yf * eve::log(ax));
    yi = inc[test](yi);
    yi = if_else(ax_is1, eve::one, yi);
    auto large = (yi > T(largelimit));
    if constexpr(real_scalar_value<T> )
    {
      if(large){
        auto zz =  (ax < one(as(x))) ? T(0) : inf(as(x));
        return ylt0 ? rec(zz) : zz;
      }
    }
    else
      yi =  if_else(large, eve::one, yi);

    auto russian = [](T base, i_t expo){
      T result(1);
      while( eve::any(to_logical(expo)) )
      {
        result *= if_else(is_odd(expo), base, T(1));
        expo = (expo >> 1);
        base = sqr(base);
      }
      return result;
    };
    z *= russian(ax, uint_(yi));
    if constexpr(!real_scalar_value<T> )
    {
      z =  if_else(large, if_else(ax < one(as(x)), zero, inf(as(x))), z);
      z =  if_else(iseqzx && ylt0, zero, z);
      z =  if_else(is_infinite(ax), inf(as(x)), z);
      z =  if_else(ylt0, rec(z), z);
    }
    else
    {
      return ylt0 ? rec(z) : z;
    }
    z =  if_else(ax_is1 || is_eqz(y), one, z);
    z =  if_else(iseqzx && is_gtz(y), zero, z);
    return z;
  }
}
