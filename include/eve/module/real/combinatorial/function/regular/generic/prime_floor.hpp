//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/any.hpp>
#include <eve/function/average.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/nth_prime.hpp>
#include <eve/function/if_else.hpp>
#include <type_traits>

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE auto prime_floor_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      auto first = T(0);
      auto last = sizeof(elt_t) == 1 ? T(53u) : T(10000);
      while (eve::any(inc(first) < last))
      {
         auto mid = average(first, last);
         auto pmid = convert(nth_prime(mid), as<elt_t>());
         auto test = pmid <= n;
         first = if_else (test, mid, first);
         last =  if_else (test, last, mid);
      }
      
      return if_else(n <= 1 || n > 104729, zero, nth_prime(first));
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
    auto r = d(prime_floor(n));
    return if_else(is_eqz(r), allbits, r);
  }
}
