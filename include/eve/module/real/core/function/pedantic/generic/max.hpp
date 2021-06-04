//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/properly_convertible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto max_(EVE_SUPPORTS(cpu_),
                            pedantic_type const &,
                            T const &v0,
                            U const &v1) noexcept
  requires properly_convertible<U, T>
  {
    return arithmetic_call(pedantic(max), v0, v1);
  }

  template<real_value T>
  EVE_FORCEINLINE auto max_(EVE_SUPPORTS(cpu_),
                            pedantic_type const &,
                            T const &v0,
                            T const &v1) noexcept
  {
    if constexpr(integral_value<T>) return eve::max(v0, v1);
    else
    {
      if constexpr(eve::platform::supports_invalids)
      {
        if constexpr(scalar_value<T>)
        {
          if (is_eqz(v0) && is_eqz(v1)) return  bit_and(v0, v1);
          return  is_unordered(v0, v1) ? v0 : eve::max(v0, v1);
        }
        else
        {
          auto tmp = if_else(is_unordered(v0, v1), v0, eve::max(v0, v1));
          return if_else(is_eqz(v0) && is_eqz(v1), bit_and(v0, v1), tmp);
        }
      }
      else
      {
        if constexpr(scalar_value<T>)
        {
          return (is_eqz(v0) && is_eqz(v1) ? bit_and(v0, v1) : eve::max(v0, v1));
        }
        else
        {
          return if_else(is_eqz(v0) && is_eqz(v1), bit_and(v0, v1), eve::max(v0, v1));
        }
      }
    }
  }
}
