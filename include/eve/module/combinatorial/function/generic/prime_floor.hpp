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
#include <typeinfo>
#include <eve/detail/apply_over.hpp>

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
      while (any(inc(first) < last))
      {
         auto mid = average(first, last);
         auto pmid = convert(primes(mid), as<elt_t>());
         auto test = pmid <= n;
         first = if_else (test, mid, first);
         last =  if_else (test, last, mid);

      }
      return primes(first);
    }
    else
      return apply_over(prime_floor, n);
  }

  template<unsigned_value T, typename D>
  EVE_FORCEINLINE constexpr auto prime_floor_(EVE_SUPPORTS(cpu_), D const &, T n) noexcept
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
      auto r =  D()(prime_floor(n));
      return if_else(is_eqz(r), allbits, r);
    }
    else
    {
      return prime_floor(D()(n));
    }
  }


}
