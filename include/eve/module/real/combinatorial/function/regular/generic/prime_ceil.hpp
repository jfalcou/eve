//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/any.hpp>
#include <eve/function/average.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/nth_prime.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE auto prime_ceil_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    using elt_t =  element_type_t<T>;
    n =  if_else(is_eqz(n), T(2), n);
    auto max_n = (sizeof(elt_t) == 1) ? T(251) : (sizeof(elt_t) == 2 ? T(65552) : T(104729));
    if constexpr(has_native_abi_v<T>)
    {
      auto first = T(0);
      auto last = sizeof(elt_t) == 1 ? T(53u) : T(10000);
      n =  if_else(n > max_n, zero, n);
      while (eve::any(inc(first) < last))
      {
        auto mid = average(first, last);
        auto pmid = nth_prime(mid);
        auto test = pmid >= n;
        last = if_else (test, mid, last);
        first =  if_else (test, first, mid);
      }
      return nth_prime(last);
    }
    else
      return apply_over(prime_ceil, n);
  }

  template<unsigned_value T, unsigned_scalar_value D>
  EVE_FORCEINLINE constexpr auto prime_ceil_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
  {
    return prime_ceil(d(n));
  }

  template<unsigned_value T, floating_scalar_value D>
  EVE_FORCEINLINE constexpr auto prime_ceil_(EVE_SUPPORTS(cpu_), converter_type<D> d, T n) noexcept
  {
    auto r = d(prime_ceil(n));
    return if_else(is_eqz(r), allbits, r);
  }
}
