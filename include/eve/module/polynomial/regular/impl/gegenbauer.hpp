//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{

template<typename I, typename T, typename U, callable_options O>
 as_wide_as_t<common_value_t<T, U>, I>
gegenbauer_(EVE_REQUIRES(cpu_), O const&, I nn, U lambda, T x)
  requires(ordered_value<U>)
{
  using c_t   = as_wide_as_t<common_value_t<T, U>, I>;
  using elt_t = element_type_t<c_t>;
  if constexpr(scalar_value<I>)
  {
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
  else
  {
    auto xx = c_t(x);
    if( has_native_abi_v<T> )
    {
      auto   y0     = one(as(xx));
      auto iseqzn   = is_eqz(nn);
      if( eve::all(iseqzn) ) return y0;
      auto n  = convert(nn, as(elt_t()));
      auto    y1 = 2 * lambda * xx;

    auto    yk = y1;
    elt_t   k(2);
    auto    k_max = n * inc(eps(as(elt_t())));
    auto    gamma = 2 * dec(lambda);
    auto    test  = k < k_max;
    while( eve::any(test) )
    {
      yk   = if_else(test, fms((2 + gamma / k) * xx, y1, inc(gamma / k) * y0), yk);
      y0   = y1;
      y1   = yk;
      k    = inc(k);
      test = k < k_max;
    }
    return if_else(iseqzn, one, yk);
  }
  else return apply_over(gegenbauer, nn, lambda, x);
  }
};


// template<scalar_value I, floating_value T, floating_ordered_value U, callable_options O>
// EVE_FORCEINLINE common_value_t<T, U>
// gegenbauer_(EVE_REQUIRES(cpu_), O const&, I nn, U lambda, T x)
// {
//   using c_t   = common_value_t<T, U>;
//   using elt_t = element_type_t<c_t>;
//   auto p0     = one(as(x));
//   if( is_eqz(nn) ) return c_t(p0);

//   c_t y0(p0);
//   c_t y1(2 * lambda * x);

//   auto  yk    = y1;
//   elt_t k     = 2;
//   elt_t k_max = nn * inc(eps(as(elt_t())));
//   c_t   gamma(2 * dec(lambda));
//   auto  test = k < k_max;
//   while( test )
//   {
//     yk = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
//     y0 = y1;
//     y1 = yk;
//     ++k;
//     test = k < k_max;
//   }
//   return yk;
// }

// template<simd_value I, floating_ordered_value T, callable_options O>
// EVE_FORCEINLINE auto
// gegenbauer_(EVE_REQUIRES(cpu_), O const&, I nn, T x) noexcept
// requires(scalar_value<T>)
// {
//   auto n =  T(nn);
//   using f_t = as_wide_t<T, cardinal_t<I>>;
//   return gegenbauer(n, f_t(x));
// }

// template<simd_value I, floating_ordered_value T, callable_options O>
// EVE_FORCEINLINE as_wide_t<T, I>
// gegenbauer_(EVE_REQUIRES(cpu_), O const&, I nn, T lambda, T x) noexcept
// requires(simd_value<T>)
// {
//   if( has_native_abi_v<T> )
//   {
//     using elt_t = element_type_t<T>;
//     T    y0     = one(as(x));
//     auto iseqzn = is_eqz(nn);
//     if( eve::all(iseqzn) ) return y0;
//     auto n  = convert(nn, as(elt_t()));
//     T    y1 = 2 * lambda * x;

//     T    yk = y1;
//     T    k(2);
//     auto k_max = n * inc(eps(as(elt_t())));
//     T    gamma = 2 * dec(lambda);
//     auto test  = k < k_max;
//     while( eve::any(test) )
//     {
//       yk   = if_else(test, fms((2 + gamma / k) * x, y1, inc(gamma / k) * y0), yk);
//       y0   = y1;
//       y1   = yk;
//       k    = inc(k);
//       test = k < k_max;
//     }
//     return if_else(iseqzn, one, yk);
//   }
//   else return apply_over(gegenbauer, nn, lambda, x);
// }

// template<simd_value I, floating_ordered_value T, floating_ordered_value U, callable_options O>
// EVE_FORCEINLINE common_value_t<T, U>
// gegenbauer_(EVE_REQUIRES(cpu_), O const&,
//             I nn,
//             U lambda,
//             T x)
// {
//   using e_t = eve::element_type_t<T>;
//     auto n = convert(nn, eve::as<e_t>());
//   using v_t = common_value_t<T, U>;
//   if constexpr( scalar_value<v_t> && simd_value<I> )
//   {
//     using w_t = as_wide_t<v_t, cardinal_t<I>>;
//     return gegenbauer(n, w_t(lambda), w_t(x));
//   }
//   else return gegenbauer(n, v_t(lambda), v_t(x));
// }
}
