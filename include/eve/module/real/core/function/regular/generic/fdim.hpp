//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/max.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto fdim_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(fdim, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T fdim_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr( unsigned_value<T> )
    {
      using elt_t = element_type_t<T>;
      auto tmp    = a - b;
      return bit_andnot(tmp, tmp >> (sizeof(elt_t) * 8 - 1));
    }
    else
    {
      if constexpr( eve::platform::supports_nans )
      {
        return if_else(is_not_less_equal(a, b), a - b, eve::zero);
      }
      else
      {
        return max(b - a, zero(eve::as(a)));
      }
    }
  }
}

