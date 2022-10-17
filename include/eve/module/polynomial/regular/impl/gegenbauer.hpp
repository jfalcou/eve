//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>

namespace eve::detail
{

template<scalar_value I, floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
gegenbauer_(EVE_SUPPORTS(cpu_), I nn, U lambda, T x) noexcept requires compatible_values<T, U>
{

  using c_t   = common_compatible_t<T, U>;
  using elt_t = element_type_t<c_t>;
  auto p0     = one(as(x));
  if( is_eqz(nn) ) return c_t(p0);

  c_t y0(p0);
  c_t y1(2 * lambda * x);

  auto  yk    = y1;
  elt_t k     = 2;
  elt_t k_max = nn * inc(eps(as(elt_t())));
  c_t   gamma(2 * dec(lambda));
  auto  test = k < k_max;
  while( test )
  {
    yk = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
    y0 = y1;
    y1 = yk;
    ++k;
    test = k < k_max;
  }
  return yk;
}

template<simd_value I, floating_real_scalar_value T>
EVE_FORCEINLINE auto
gegenbauer_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
{
  auto n =  T(nn);
  using f_t = as_wide_t<T, cardinal_t<I>>;
  return gegenbauer(n, f_t(x));
}

template<simd_value I, floating_real_simd_value T>
EVE_FORCEINLINE auto
gegenbauer_(EVE_SUPPORTS(cpu_), I nn, T lambda, T x) noexcept
{
  if( has_native_abi_v<T> )
  {
    using elt_t = element_type_t<T>;
    T    y0     = one(as(x));
    auto iseqzn = is_eqz(nn);
    if( eve::all(iseqzn) ) return y0;
    auto n  = convert(nn, as(elt_t()));
    T    y1 = 2 * lambda * x;

    T    yk = y1;
    T    k(2);
    auto k_max = n * inc(eps(as(elt_t())));
    T    gamma = 2 * dec(lambda);
    auto test  = k < k_max;
    while( eve::any(test) )
    {
      yk   = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
      y0   = y1;
      y1   = yk;
      k    = inc(k);
      test = k < k_max;
    }
    return if_else(iseqzn, one, yk);
  }
  else return apply_over(gegenbauer, nn, lambda, x);
}

template<simd_value I, floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
gegenbauer_(EVE_SUPPORTS(cpu_),
            I nn,
            U lambda,
            T x) noexcept requires compatible_values<T, U>
{
  using e_t = eve::element_type_t<T>;
    auto n = convert(nn, eve::as<e_t>());
  using v_t = common_compatible_t<T, U>;
  if constexpr( scalar_value<v_t> && simd_value<I> )
  {
    using w_t = as_wide_t<v_t, cardinal_t<I>>;
    return gegenbauer(n, w_t(lambda), w_t(x));
  }
  else return gegenbauer(n, v_t(lambda), v_t(x));
}
}
