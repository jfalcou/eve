//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_SHR_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/shr.hpp>

#include <type_traits>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE T bit_shr_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> && has_native_abi_v<U> )
    {
      using u_t = eve::detail::as_integer_t<T, unsigned>;
      if constexpr( scalar_value<U> )
      {
        if constexpr( scalar_value<T> )
          return static_cast<T>(u_t(a) >> b);
        else if constexpr( simd_value<T> )
          return bit_cast(shr(bit_cast(a, as_<u_t>()), int(b)), as(a));
      }
      else
        return bit_cast(map(bit_shr, a, b), as(a));
    }
    else
      return apply_over(bit_shr, a, b);
  }
}

#endif
