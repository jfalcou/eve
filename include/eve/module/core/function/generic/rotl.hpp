//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ROTL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ROTL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
#include <eve/detail/meta/traits.hpp>

namespace eve::detail
{
  template<unsigned_value T, integral_value U>
  EVE_FORCEINLINE  auto rotl_(EVE_SUPPORTS(cpu_)
                          , T a0
                          , U n) noexcept
  {
    if constexpr(has_native_abi_v<T> && scalar_value<U>)
    {
      if (n == 0) return a0;
      using elt_t = element_type_t<T>;
      constexpr U width = sizeof(elt_t) * 8 - 1 ;
      n &= width;
      if (n > 0)
      {
        a0 = (a0 << n) | (a0 >>  (-n&width));
      }
      else
      {
        n = -n; //this is to allow the compiler to produce a ror instruction
        a0 = (a0 >> n) | (a0 << (-n&width));
      }
      return a0;
    }
    else if constexpr(scalar_value<T> && has_native_abi_v<U>)
    {
      using r_t = as_wide<T, cardinal_t<U>>;
      return rotl(r_t(a0), n);
    }
    // now none is scalar
    else if constexpr(has_emulated_abi_v<T> || has_emulated_abi_v<U>)
    {
      return map(rotl, a0, n);
    }
    else if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)
    {
      return aggregate(rotl, a0, n);
    }
    else if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      return map(eve::rotl, a0, n);
    }
  }

}

#endif
