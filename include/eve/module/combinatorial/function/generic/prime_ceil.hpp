//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/any.hpp>
#include <eve/function/average.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/primes.hpp>
#include <eve/function/if_else.hpp>
#include <type_traits>
#include <eve/detail/apply_over.hpp>

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
      while (any(inc(first) < last))
      {
        auto mid = average(first, last);
        auto pmid = primes(mid);
        auto test = pmid >= n;
        last = if_else (test, mid, last);
        first =  if_else (test, first, mid);
      }
      return primes(last);
    }
    else
      return apply_over(prime_ceil, n);
  }

  template<unsigned_value T, typename D>
  EVE_FORCEINLINE constexpr auto prime_ceil_(EVE_SUPPORTS(cpu_), D const &, T n) noexcept
  requires(is_one_of<D>(types<
                        converter_type<std::uint8_t>
                       , converter_type<std::uint16_t>
                       , converter_type<std::uint32_t>
                       , converter_type<std::uint64_t>
                       , converter_type<float>
                       , converter_type<double>>{}))
  {
    if constexpr(is_one_of<D>(types<converter_type<float>, converter_type<double>>{}))
    {
      auto r =  D()(prime_ceil(n));
      return if_else(is_eqz(r), allbits, r);
    }
    else
    {
      return prime_ceil(D()(n));
    }
  }


}
