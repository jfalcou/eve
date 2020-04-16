//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_LOGICAL_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_LOGICAL_NOT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
           if constexpr(logical_simd_value<T>)   return eve::bit_cast(eve::bit_not(a.bits()),as(a));
      else if constexpr(logical_scalar_value<T>) return T(a.not_value());
      else                                       return is_eqz(a);
    }
    else                                         return apply_over(logical_not, a);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<value T>
  EVE_FORCEINLINE auto operator!(T const &v) noexcept -> decltype(eve::logical_not(v))
  {
    return eve::logical_not(v);
  }
}
#endif
