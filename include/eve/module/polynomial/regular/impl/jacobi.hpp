//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{

template<scalar_value I, floating_value T, floating_value U, floating_value V>
EVE_FORCEINLINE auto
jacobi_(EVE_SUPPORTS(cpu_), I n, U alpha, V beta, T x) noexcept
{
  EVE_ASSERT(is_flint(n), "n is not flint");
  using r_t = common_compatible_t<T, U, V>;
  if( n == 0 ) return r_t(1);
  r_t  y0(1);
  auto ap1   = inc(alpha);
  auto apb   = alpha + beta;
  auto a2mb2 = sqr(alpha) - sqr(beta);
  auto y1    = fam(ap1, (apb + 2), (x - 1) * r_t(0.5));

  r_t yk = y1;
  I   k(2);
  I   k2(4);
  while( k <= n )
  {
    auto apbpk  = k + apb;
    auto apbpk2 = k + apbpk;
    auto denom  = k2 * apbpk * (apbpk2 - 2);
    auto gamma1 = (apbpk2 - 1) * fma(apbpk2 * (apbpk2 - 2), x, a2mb2);
    auto gamma0 = -2 * (k + alpha - 1) * (k + beta - 1) * apbpk2;
    yk = fma(gamma1, y1, gamma0 * y0) / denom; // sum_of_prod(gamma1, y1, gamma0, y0)/denom;
    y0 = y1;
    y1 = yk;
    ++k;
    k2 += 2;
  }
  return yk;
}

template<simd_value I, floating_value T, floating_value U, floating_value V>
EVE_FORCEINLINE auto
jacobi_(EVE_SUPPORTS(cpu_), I nn, U aalpha, V abeta, T xx) noexcept
{
  using f_t   = common_compatible_t<T, U, V>;
  using r_t   = as_wide_t<f_t, cardinal_t<I>>;
  using elt_t = element_type_t<r_t>;
  r_t n(to_<elt_t>(nn));
  r_t alpha(to_<elt_t>(aalpha));
  r_t beta(to_<elt_t>(abeta));
  r_t x(to_<elt_t>(xx));
  return arithmetic_call(jacobi, n, alpha, beta, x);
}

template<floating_simd_value T>
EVE_FORCEINLINE auto
jacobi_(EVE_SUPPORTS(cpu_), T n, T alpha, T beta, T x) noexcept
{
  EVE_ASSERT(eve::all(is_flint(n)), "some elements of n are not flint");
  if constexpr( has_native_abi_v<T> )
  {
    T    y0(1);
    auto ap1   = inc(alpha);
    auto apb   = alpha + beta;
    auto a2mb2 = sqr(alpha) - sqr(beta);
    auto y1    = fam(ap1, (apb + 2), (x - 1) * T(0.5));
    T    yk    = y1;
    T    k(2);
    T    k2(4);
    auto test = k <= n;
    while( eve::any(test) )
    {
      T apbpk  = k + apb;
      T apbpk2 = k + apbpk;
      T denom  = k2 * apbpk * (apbpk2 - 2);
      T gamma1 = (apbpk2 - 1) * fma(apbpk2 * (apbpk2 - 2), x, a2mb2);
      T gamma0 = -2 * (k + alpha - 1) * (k + beta - 1) * apbpk2;
      yk       = if_else(test,
                   fma(gamma1, y1, gamma0 * y0) / denom,
                   yk); // sum_of_prod(gamma1, y1, gamma0, y0)/denom, yk);
      y0       = y1;
      y1       = yk;
      k        = inc(k);
      k2 += 2;
      test = k <= n;
    }
    return if_else(is_eqz(n), one(as(yk)), yk);
  }
  else return apply_over(jacobi, n, alpha, beta, x);
}
}
