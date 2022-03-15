//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/combinatorial/regular/nth_prime.hpp>
#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE auto prime_floor_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      auto constexpr maxi = (sizeof(elt_t) == 1) ? (53u) : ((sizeof(elt_t) == 2) ? (6541u) : (10000u));
      auto constexpr next = (sizeof(elt_t) == 1) ? (255u): ((sizeof(elt_t) == 2) ? (65535u): (104742u));
      auto first = T(0);
      auto last = T(maxi);
      while (eve::any(inc(first) < last))
      {
        auto mid = average(first, last);
        auto pmid = convert(nth_prime(mid), as<elt_t>());
        auto test = pmid <= n;
        first = if_else (test, mid, first);
        last =  if_else (test, last, mid);
      }
      auto z = nth_prime(first);
      z =  if_else((((last == T(maxi)) && (n < T(next))) || (first < T(maxi-1))) && (n > 2), z, zero);
      return z;
    }
    else
      return apply_over(prime_floor, n);
  }

  template<unsigned_value T, unsigned_scalar_value D>
  EVE_FORCEINLINE constexpr auto prime_floor_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
  {
    return prime_floor(d(n));
  }

  template<unsigned_value T, floating_scalar_value D>
  EVE_FORCEINLINE constexpr auto prime_floor_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
  {
    using ui_t = as_integer_t<D, unsigned>;
    auto nn = convert(n, eve::as(ui_t()));
    auto r = d(prime_floor(nn));
    return if_else(is_eqz(r), allbits, r);
  }
}
