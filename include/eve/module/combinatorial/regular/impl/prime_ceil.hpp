//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/combinatorial/regular/nth_prime.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
template<unsigned_value T>
EVE_FORCEINLINE auto
prime_ceil_(EVE_SUPPORTS(cpu_), T n) noexcept
{
  using elt_t = element_type_t<T>;
  n           = if_else(is_eqz(n), T(2), n);
  auto max_n  = (sizeof(elt_t) == 1) ? T(53) : (sizeof(elt_t) == 2 ? T(6541) : T(9999));
  if constexpr( has_native_abi_v<T> )
  {
    auto first  = T(0);
    auto last   = max_n;
    auto toobig = n > nth_prime(max_n);
    n           = if_else(toobig, zero, n);
    while( eve::any(inc(first) < last) )
    {
      T    mid  = average(first, last);
      auto pmid = nth_prime(mid);
      auto test = pmid >= n;
      last      = if_else(test, mid, last);
      first     = if_else(test, first, mid);
    }
    auto tmp = nth_prime(first);
    auto t   = tmp >= n;
    return if_else(toobig, zero, if_else(t, tmp, nth_prime(last)));
  }
  else return apply_over(prime_ceil, n);
}

template<unsigned_value T, unsigned_scalar_value D>
EVE_FORCEINLINE constexpr auto
prime_ceil_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
{
  return prime_ceil(d(n));
}

template<unsigned_value T, floating_scalar_value D>
EVE_FORCEINLINE constexpr auto
prime_ceil_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
{
  auto r = d(prime_ceil(n));
  return if_else(is_eqz(r), allbits, r);
}
}
