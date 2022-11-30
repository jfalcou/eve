//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/detail/generic/pow_kernel.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
pow_abs_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(eve::pow(eve::abs(a), b))
{
  return arithmetic_call(pow_abs, a, b);
}

template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
pow_abs_(EVE_SUPPORTS(cpu_),
         raw_type const&,
         T const& a,
         U const& b) noexcept
-> decltype(eve::pow(eve::abs(a), b))
{
  return arithmetic_call(raw(pow_abs), a, b);
}

template<floating_real_value T>
EVE_FORCEINLINE auto
pow_abs_(EVE_SUPPORTS(cpu_), raw_type const&, T a, T b) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::exp(b * eve::log(eve::abs(a))); }
  else return apply_over(raw(pow_abs), a, b);
}

template<floating_real_value T>
auto
pow_abs_(EVE_SUPPORTS(cpu_), T x, T y) noexcept
{
  if constexpr( scalar_value<T> ) return std::pow(eve::abs(x), y);
  if constexpr( has_native_abi_v<T> )
  {
    using i_t              = as_integer_t<T, unsigned>;
    using eli_t            = element_type_t<i_t>;
    auto        iseqzx     = is_eqz(x);
    auto        ylt0       = y < zero(as(y));
    auto        ax         = eve::abs(x);
    auto        ax_is1     = ax == eve::one(as(x));
    eli_t const largelimit = (sizeof(eli_t) == 4 ? 31 : 63);
    auto [yf, yi]          = eve::modf(eve::abs(y));
    auto test              = yf > T(0.5);
    yf                     = dec[test](yf);
    auto z                 = eve::exp(yf * eve::log(ax));
    yi                     = inc[test](yi);
    yi                     = if_else(ax_is1, eve::one, yi);
    auto large             = (yi > T(largelimit));
    yi                     = if_else(large, eve::one, yi);

    auto russian = [](T base, i_t expo)
    {
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
    z = if_else(large, if_else(ax < one(as(x)), zero, inf(as(x))), z);
    z = if_else(iseqzx && ylt0, zero, z);
    z = if_else(is_infinite(ax), inf(as(x)), z);
    z = if_else(ylt0, rec(z), z);
    z = if_else(ax_is1 || is_eqz(y), one, z);
    z = if_else(iseqzx && is_gtz(y), zero, z);
    z = if_else(is_nan(x) && is_nan(y), allbits, z);
    return z;
  }
  else return apply_over(pow_abs, x, y);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
pow_abs_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, V const& v) noexcept
-> decltype( if_else(cond, pow_abs(t, v), t) )
{
  return mask_op(cond, eve::pow_abs, t, v);
}

template<conditional_expr C, decorator D, value U, value V>
EVE_FORCEINLINE auto
pow_abs_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t, V const& v) noexcept
-> decltype( if_else(cond, pow_abs(t, v), t) )
{
  return mask_op(cond, d(eve::pow_abs), t, v);
}
}
