//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve::detail
{
//////////////////////////////////////////////////////////////////
// raw
template<floating_ordered_value T, integral_scalar_value I>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), raw_type const&, T x, I n) noexcept
{
  return raw(nthroot)(x, T(n));
}

template<floating_ordered_value T, integral_simd_value I>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), raw_type const&, T x, I n) noexcept
    requires(cardinal_v<T> == cardinal_v<I>)
{
  using elt_t = element_type_t<T>;
  return raw(nthroot)(x, convert(n, as<elt_t>()));
}

template<floating_ordered_value T>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), raw_type const&, T x, T n) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto r      = pow(abs(x), rec(n));
    auto islezx = is_lez(x);
    if( none(islezx) ) return r;
    else
      return if_else(is_eqz(x),
                     if_else(is_ltz(n), inf(as(x)), zero),
                     if_else(islezx && !is_odd(n), allbits, r * sign(x)));
  }
  else return apply_over(raw(nthroot), x, n);
}

//////////////////////////////////////////////////////////////////
// regular
template<floating_ordered_value T, integral_scalar_value I>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), T x, I n) noexcept
{
  return nthroot(x, T(n));
}

template<floating_ordered_value T, integral_simd_value I>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), T x, I n) noexcept requires(cardinal_v<T> == cardinal_v<I>)
{
  using elt_t = element_type_t<T>;
  return nthroot(x, convert(n, as<elt_t>()));
}

template<floating_ordered_value T>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), T x, T n) noexcept
{
  auto an   = abs(n);
  auto ax   = eve::abs(x);
  auto y    = raw(nthroot)(ax, an);
  auto p    = pow(y, an);
  auto yinc = -((p - ax) / (an * p)) * y;
  y         = add[is_nez(y) && is_finite(x)](y, yinc);
  y         = if_else(is_negative(x) && is_even(an), allbits, y * sign(x));
  return if_else(is_ltz(n), rec(y), y);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U, integral_value N>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, N const& n) noexcept
{
  return mask_op(cond, eve::nthroot, t, n);
}

template<conditional_expr C, decorator D, value U, integral_value N>
EVE_FORCEINLINE auto
nthroot_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t, N const& n) noexcept
{
  return mask_op(cond, d(eve::nthroot), t, n);
}
}
